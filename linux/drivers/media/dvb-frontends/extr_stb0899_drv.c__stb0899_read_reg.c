#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u8 ;
struct stb0899_state {scalar_t__* verbose; int /*<<< orphan*/  i2c; TYPE_1__* config; } ;
struct i2c_msg {unsigned int* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  demod_address; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int ERESTARTSYS ; 
 scalar_t__ FE_DEBUGREG ; 
 int /*<<< orphan*/  FE_ERROR ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  dprintk (scalar_t__*,int /*<<< orphan*/ ,int,char*,unsigned int,unsigned int) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int _stb0899_read_reg(struct stb0899_state *state, unsigned int reg)
{
	int ret;

	u8 b0[] = { reg >> 8, reg & 0xff };
	u8 buf;

	struct i2c_msg msg[] = {
		{
			.addr	= state->config->demod_address,
			.flags	= 0,
			.buf	= b0,
			.len	= 2
		},{
			.addr	= state->config->demod_address,
			.flags	= I2C_M_RD,
			.buf	= &buf,
			.len	= 1
		}
	};

	ret = i2c_transfer(state->i2c, msg, 2);
	if (ret != 2) {
		if (ret != -ERESTARTSYS)
			dprintk(state->verbose, FE_ERROR, 1,
				"Read error, Reg=[0x%02x], Status=%d",
				reg, ret);

		return ret < 0 ? ret : -EREMOTEIO;
	}
	if (unlikely(*state->verbose >= FE_DEBUGREG))
		dprintk(state->verbose, FE_ERROR, 1, "Reg=[0x%02x], data=%02x",
			reg, buf);

	return (unsigned int)buf;
}