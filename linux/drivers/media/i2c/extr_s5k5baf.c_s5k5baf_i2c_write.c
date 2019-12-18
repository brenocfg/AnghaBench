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
typedef  int u8 ;
typedef  int u16 ;
struct s5k5baf {int error; int /*<<< orphan*/  sd; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug ; 
 int i2c_master_send (struct i2c_client*,int*,int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct i2c_client*,char*,int,int) ; 
 int /*<<< orphan*/  v4l2_err (struct i2c_client*,char*,int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void s5k5baf_i2c_write(struct s5k5baf *state, u16 addr, u16 val)
{
	u8 buf[4] = { addr >> 8, addr & 0xFF, val >> 8, val & 0xFF };
	struct i2c_client *c = v4l2_get_subdevdata(&state->sd);
	int ret;

	if (state->error)
		return;

	ret = i2c_master_send(c, buf, 4);
	v4l2_dbg(3, debug, c, "i2c_write: 0x%04x : 0x%04x\n", addr, val);

	if (ret != 4) {
		v4l2_err(c, "i2c_write: error during transfer (%d)\n", ret);
		state->error = ret;
	}
}