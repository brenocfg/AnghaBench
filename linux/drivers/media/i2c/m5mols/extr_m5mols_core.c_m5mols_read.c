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
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct m5mols_info {scalar_t__ isp_ready; } ;
struct i2c_msg {int len; int* buf; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int I2C_CATEGORY (int) ; 
 int I2C_COMMAND (int) ; 
 scalar_t__ I2C_M_RD ; 
 int M5MOLS_BYTE_READ ; 
 int /*<<< orphan*/  M5MOLS_I2C_MAX_SIZE ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int m5mols_swap_byte (int*,int) ; 
 struct m5mols_info* to_m5mols (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*,int,int,int,int) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int m5mols_read(struct v4l2_subdev *sd, u32 size, u32 reg, u32 *val)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct m5mols_info *info = to_m5mols(sd);
	u8 rbuf[M5MOLS_I2C_MAX_SIZE + 1];
	u8 category = I2C_CATEGORY(reg);
	u8 cmd = I2C_COMMAND(reg);
	struct i2c_msg msg[2];
	u8 wbuf[5];
	int ret;

	if (!client->adapter)
		return -ENODEV;

	msg[0].addr = client->addr;
	msg[0].flags = 0;
	msg[0].len = 5;
	msg[0].buf = wbuf;
	wbuf[0] = 5;
	wbuf[1] = M5MOLS_BYTE_READ;
	wbuf[2] = category;
	wbuf[3] = cmd;
	wbuf[4] = size;

	msg[1].addr = client->addr;
	msg[1].flags = I2C_M_RD;
	msg[1].len = size + 1;
	msg[1].buf = rbuf;

	/* minimum stabilization time */
	usleep_range(200, 300);

	ret = i2c_transfer(client->adapter, msg, 2);

	if (ret == 2) {
		*val = m5mols_swap_byte(&rbuf[1], size);
		return 0;
	}

	if (info->isp_ready)
		v4l2_err(sd, "read failed: size:%d cat:%02x cmd:%02x. %d\n",
			 size, category, cmd, ret);

	return ret < 0 ? ret : -EIO;
}