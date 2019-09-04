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
typedef  int /*<<< orphan*/  u16 ;
struct s5k5baf {int error; int /*<<< orphan*/  sd; } ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct i2c_client*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (struct i2c_client*,char*,int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u16 s5k5baf_i2c_read(struct s5k5baf *state, u16 addr)
{
	struct i2c_client *c = v4l2_get_subdevdata(&state->sd);
	__be16 w, r;
	u16 res;
	struct i2c_msg msg[] = {
		{ .addr = c->addr, .flags = 0,
		  .len = 2, .buf = (u8 *)&w },
		{ .addr = c->addr, .flags = I2C_M_RD,
		  .len = 2, .buf = (u8 *)&r },
	};
	int ret;

	if (state->error)
		return 0;

	w = cpu_to_be16(addr);
	ret = i2c_transfer(c->adapter, msg, 2);
	res = be16_to_cpu(r);

	v4l2_dbg(3, debug, c, "i2c_read: 0x%04x : 0x%04x\n", addr, res);

	if (ret != 2) {
		v4l2_err(c, "i2c_read: error during transfer (%d)\n", ret);
		state->error = ret;
	}
	return res;
}