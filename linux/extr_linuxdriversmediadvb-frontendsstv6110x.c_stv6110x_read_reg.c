#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct stv6110x_state {int /*<<< orphan*/  i2c; struct stv6110x_config* config; } ;
struct stv6110x_config {int /*<<< orphan*/  addr; } ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  FE_ERROR ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int stv6110x_read_reg(struct stv6110x_state *stv6110x, u8 reg, u8 *data)
{
	int ret;
	const struct stv6110x_config *config = stv6110x->config;
	u8 b0[] = { reg };
	u8 b1[] = { 0 };
	struct i2c_msg msg[] = {
		{ .addr = config->addr, .flags = 0,	   .buf = b0, .len = 1 },
		{ .addr = config->addr, .flags = I2C_M_RD, .buf = b1, .len = 1 }
	};

	ret = i2c_transfer(stv6110x->i2c, msg, 2);
	if (ret != 2) {
		dprintk(FE_ERROR, 1, "I/O Error");
		return -EREMOTEIO;
	}
	*data = b1[0];

	return 0;
}