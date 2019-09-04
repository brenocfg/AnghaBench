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
struct v4l2_subdev {int dummy; } ;
struct i2c_reg_value {scalar_t__ reg; scalar_t__ type; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 scalar_t__ TVP7002_EOR ; 
 scalar_t__ TVP7002_WRITE ; 
 int /*<<< orphan*/  tvp7002_write_err (struct v4l2_subdev*,scalar_t__,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int tvp7002_write_inittab(struct v4l2_subdev *sd,
					const struct i2c_reg_value *regs)
{
	int error = 0;

	/* Initialize the first (defined) registers */
	while (TVP7002_EOR != regs->reg) {
		if (TVP7002_WRITE == regs->type)
			tvp7002_write_err(sd, regs->reg, regs->value, &error);
		regs++;
	}

	return error;
}