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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct i2c_msg {int dummy; } ;
struct TYPE_8__ {int i2c_addr; int /*<<< orphan*/  i2c_adap; } ;
struct TYPE_6__ {scalar_t__ fw_is_running; } ;
struct TYPE_7__ {TYPE_1__ risc; } ;
struct dib9000_state {int* i2c_write_buffer; TYPE_4__* msg; TYPE_3__ i2c; TYPE_2__ platform; } ;
typedef  int reg ;
struct TYPE_9__ {int addr; int* buf; scalar_t__ len; scalar_t__ flags; } ;

/* Variables and functions */
 int DATA_BUS_ACCESS_MODE_16BIT ; 
 int DATA_BUS_ACCESS_MODE_8BIT ; 
 int DATA_BUS_ACCESS_MODE_NO_ADDRESS_INCREMENT ; 
 int EINVAL ; 
 int EREMOTEIO ; 
 scalar_t__ dib9000_risc_apb_access_write (struct dib9000_state*,int,int,int /*<<< orphan*/  const*,scalar_t__) ; 
 int i2c_transfer (int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dib9000_write16_attr(struct dib9000_state *state, u16 reg, const u8 *buf, u32 len, u16 attribute)
{
	u32 chunk_size = 126;
	u32 l;
	int ret;

	if (state->platform.risc.fw_is_running && (reg < 1024)) {
		if (dib9000_risc_apb_access_write
		    (state, reg, DATA_BUS_ACCESS_MODE_16BIT | DATA_BUS_ACCESS_MODE_NO_ADDRESS_INCREMENT | attribute, buf, len) != 0)
			return -EINVAL;
		return 0;
	}

	memset(&state->msg[0], 0, sizeof(struct i2c_msg));
	state->msg[0].addr = state->i2c.i2c_addr >> 1;
	state->msg[0].flags = 0;
	state->msg[0].buf = state->i2c_write_buffer;
	state->msg[0].len = len + 2;

	state->i2c_write_buffer[0] = (reg >> 8) & 0xff;
	state->i2c_write_buffer[1] = (reg) & 0xff;

	if (attribute & DATA_BUS_ACCESS_MODE_8BIT)
		state->i2c_write_buffer[0] |= (1 << 5);
	if (attribute & DATA_BUS_ACCESS_MODE_NO_ADDRESS_INCREMENT)
		state->i2c_write_buffer[0] |= (1 << 4);

	do {
		l = len < chunk_size ? len : chunk_size;
		state->msg[0].len = l + 2;
		memcpy(&state->i2c_write_buffer[2], buf, l);

		ret = i2c_transfer(state->i2c.i2c_adap, state->msg, 1) != 1 ? -EREMOTEIO : 0;

		buf += l;
		len -= l;

		if (!(attribute & DATA_BUS_ACCESS_MODE_NO_ADDRESS_INCREMENT))
			reg += l / 2;
	} while ((ret == 0) && len);

	return ret;
}