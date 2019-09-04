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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int I2C_SIZE (int /*<<< orphan*/ ) ; 
 int m5mols_read (struct v4l2_subdev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*) ; 

int m5mols_read_u32(struct v4l2_subdev *sd, u32 reg, u32 *val)
{
	if (I2C_SIZE(reg) != 4) {
		v4l2_err(sd, "Wrong data size\n");
		return -EINVAL;
	}

	return m5mols_read(sd, I2C_SIZE(reg), reg, val);
}