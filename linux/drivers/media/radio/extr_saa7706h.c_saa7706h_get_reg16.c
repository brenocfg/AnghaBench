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
struct v4l2_subdev {int dummy; } ;
struct i2c_msg {int len; int* buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  regaddr ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct i2c_msg*) ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int saa7706h_i2c_transfer (struct i2c_client*,struct i2c_msg*,int /*<<< orphan*/ ) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int saa7706h_get_reg16(struct v4l2_subdev *sd, u16 reg)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	u8 buf[2];
	int err;
	u8 regaddr[] = {reg >> 8, reg};
	struct i2c_msg msg[] = {
					{
						.addr = client->addr,
						.len = sizeof(regaddr),
						.buf = regaddr
					},
					{
						.addr = client->addr,
						.flags = I2C_M_RD,
						.len = sizeof(buf),
						.buf = buf
					}
				};

	err = saa7706h_i2c_transfer(client, msg, ARRAY_SIZE(msg));
	if (err)
		return err;

	return buf[0] << 8 | buf[1];
}