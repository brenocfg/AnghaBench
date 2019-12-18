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
typedef  scalar_t__ u16 ;
struct v4l2_subdev {int dummy; } ;
struct mt9v111_dev {scalar_t__ addr_space; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MT9V111_R01_ADDR_SPACE ; 
 int __mt9v111_read (struct i2c_client*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int __mt9v111_write (struct i2c_client*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct v4l2_subdev* i2c_get_clientdata (struct i2c_client*) ; 
 struct mt9v111_dev* sd_to_mt9v111 (struct v4l2_subdev*) ; 

__attribute__((used)) static int __mt9v111_addr_space_select(struct i2c_client *c, u16 addr_space)
{
	struct v4l2_subdev *sd = i2c_get_clientdata(c);
	struct mt9v111_dev *mt9v111 = sd_to_mt9v111(sd);
	u16 val;
	int ret;

	if (mt9v111->addr_space == addr_space)
		return 0;

	ret = __mt9v111_write(c, MT9V111_R01_ADDR_SPACE, addr_space);
	if (ret)
		return ret;

	/* Verify address space has been updated */
	ret = __mt9v111_read(c, MT9V111_R01_ADDR_SPACE, &val);
	if (ret)
		return ret;

	if (val != addr_space)
		return -EINVAL;

	mt9v111->addr_space = addr_space;

	return 0;
}