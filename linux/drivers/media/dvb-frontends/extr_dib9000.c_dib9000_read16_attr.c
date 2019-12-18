#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct i2c_msg {int dummy; } ;
struct TYPE_8__ {int i2c_addr; int /*<<< orphan*/  i2c_adap; } ;
struct TYPE_6__ {scalar_t__ fw_is_running; } ;
struct TYPE_7__ {TYPE_1__ risc; } ;
struct dib9000_state {int* i2c_write_buffer; TYPE_4__* msg; TYPE_3__ i2c; TYPE_2__ platform; } ;
struct TYPE_9__ {int addr; int* buf; int len; scalar_t__ flags; } ;

/* Variables and functions */
 int DATA_BUS_ACCESS_MODE_8BIT ; 
 int DATA_BUS_ACCESS_MODE_NO_ADDRESS_INCREMENT ; 
 int EREMOTEIO ; 
 scalar_t__ I2C_M_RD ; 
 int dib9000_risc_apb_access_read (struct dib9000_state*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,scalar_t__) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int i2c_transfer (int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dib9000_read16_attr(struct dib9000_state *state, u16 reg, u8 *b, u32 len, u16 attribute)
{
	u32 chunk_size = 126;
	u32 l;
	int ret;

	if (state->platform.risc.fw_is_running && (reg < 1024))
		return dib9000_risc_apb_access_read(state, reg, attribute, NULL, 0, b, len);

	memset(state->msg, 0, 2 * sizeof(struct i2c_msg));
	state->msg[0].addr = state->i2c.i2c_addr >> 1;
	state->msg[0].flags = 0;
	state->msg[0].buf = state->i2c_write_buffer;
	state->msg[0].len = 2;
	state->msg[1].addr = state->i2c.i2c_addr >> 1;
	state->msg[1].flags = I2C_M_RD;
	state->msg[1].buf = b;
	state->msg[1].len = len;

	state->i2c_write_buffer[0] = reg >> 8;
	state->i2c_write_buffer[1] = reg & 0xff;

	if (attribute & DATA_BUS_ACCESS_MODE_8BIT)
		state->i2c_write_buffer[0] |= (1 << 5);
	if (attribute & DATA_BUS_ACCESS_MODE_NO_ADDRESS_INCREMENT)
		state->i2c_write_buffer[0] |= (1 << 4);

	do {
		l = len < chunk_size ? len : chunk_size;
		state->msg[1].len = l;
		state->msg[1].buf = b;
		ret = i2c_transfer(state->i2c.i2c_adap, state->msg, 2) != 2 ? -EREMOTEIO : 0;
		if (ret != 0) {
			dprintk("i2c read error on %d\n", reg);
			return -EREMOTEIO;
		}

		b += l;
		len -= l;

		if (!(attribute & DATA_BUS_ACCESS_MODE_NO_ADDRESS_INCREMENT))
			reg += l / 2;
	} while ((ret == 0) && len);

	return 0;
}