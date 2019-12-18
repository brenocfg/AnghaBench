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
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct noon010_info {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int i2c_smbus_write_byte_data (struct i2c_client*,int,int) ; 
 int set_i2c_page (struct noon010_info*,struct i2c_client*,int) ; 
 struct noon010_info* to_noon010 (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int cam_i2c_write(struct v4l2_subdev *sd, u32 reg_addr, u32 val)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct noon010_info *info = to_noon010(sd);
	int ret = set_i2c_page(info, client, reg_addr);

	if (ret)
		return ret;
	return i2c_smbus_write_byte_data(client, reg_addr & 0xFF, val);
}