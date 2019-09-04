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
typedef  int /*<<< orphan*/  val ;
typedef  char u8 ;
struct v4l2_subdev {int dummy; } ;
struct i2c_msg {int len; char* buf; int flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  reg ;

/* Variables and functions */
 int ARRAY_SIZE (struct i2c_msg*) ; 
 int I2C_M_NO_RD_ACK ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  debug ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static u8 ks0127_read(struct v4l2_subdev *sd, u8 reg)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	char val = 0;
	struct i2c_msg msgs[] = {
		{
			.addr = client->addr,
			.len = sizeof(reg),
			.buf = &reg
		},
		{
			.addr = client->addr,
			.flags = I2C_M_RD | I2C_M_NO_RD_ACK,
			.len = sizeof(val),
			.buf = &val
		}
	};
	int ret;

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	if (ret != ARRAY_SIZE(msgs))
		v4l2_dbg(1, debug, sd, "read error\n");

	return val;
}