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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int I2C_SIZE (scalar_t__) ; 
 int m5mols_read (struct v4l2_subdev*,int,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*) ; 

int m5mols_read_u16(struct v4l2_subdev *sd, u32 reg, u16 *val)
{
	u32 val_32;
	int ret;

	if (I2C_SIZE(reg) != 2) {
		v4l2_err(sd, "Wrong data size\n");
		return -EINVAL;
	}

	ret = m5mols_read(sd, I2C_SIZE(reg), reg, &val_32);
	if (ret)
		return ret;

	*val = (u16)val_32;
	return ret;
}