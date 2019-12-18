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
typedef  int u8 ;
struct stb6100_state {TYPE_1__* config; int /*<<< orphan*/  i2c; } ;
struct i2c_msg {int* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  tuner_address; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 scalar_t__ FE_DEBUG ; 
 scalar_t__ FE_ERROR ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int STB6100_NUMREGS ; 
 int /*<<< orphan*/  dprintk (scalar_t__,scalar_t__,int,char*,int /*<<< orphan*/ ,...) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/ * stb6100_regnames ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int stb6100_read_regs(struct stb6100_state *state, u8 regs[])
{
	int rc;
	struct i2c_msg msg = {
		.addr	= state->config->tuner_address,
		.flags	= I2C_M_RD,
		.buf	= regs,
		.len	= STB6100_NUMREGS
	};

	rc = i2c_transfer(state->i2c, &msg, 1);
	if (unlikely(rc != 1)) {
		dprintk(verbose, FE_ERROR, 1, "Read (0x%x) err, rc=[%d]",
			state->config->tuner_address, rc);

		return -EREMOTEIO;
	}
	if (unlikely(verbose > FE_DEBUG)) {
		int i;

		dprintk(verbose, FE_DEBUG, 1, "    Read from 0x%02x", state->config->tuner_address);
		for (i = 0; i < STB6100_NUMREGS; i++)
			dprintk(verbose, FE_DEBUG, 1, "        %s: 0x%02x", stb6100_regnames[i], regs[i]);
	}
	return 0;
}