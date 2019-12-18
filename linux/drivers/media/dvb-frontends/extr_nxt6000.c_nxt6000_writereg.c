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
typedef  int /*<<< orphan*/  u8 ;
struct nxt6000_state {int /*<<< orphan*/  i2c; TYPE_1__* config; } ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  demod_address; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int nxt6000_writereg(struct nxt6000_state* state, u8 reg, u8 data)
{
	u8 buf[] = { reg, data };
	struct i2c_msg msg = {.addr = state->config->demod_address,.flags = 0,.buf = buf,.len = 2 };
	int ret;

	if ((ret = i2c_transfer(state->i2c, &msg, 1)) != 1)
		dprintk("nxt6000: nxt6000_write error (reg: 0x%02X, data: 0x%02X, ret: %d)\n", reg, data, ret);

	return (ret != 1) ? -EIO : 0;
}