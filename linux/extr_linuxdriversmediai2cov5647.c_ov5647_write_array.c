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
struct regval_list {int /*<<< orphan*/  data; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int ov5647_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov5647_write_array(struct v4l2_subdev *sd,
				struct regval_list *regs, int array_size)
{
	int i, ret;

	for (i = 0; i < array_size; i++) {
		ret = ov5647_write(sd, regs[i].addr, regs[i].data);
		if (ret < 0)
			return ret;
	}

	return 0;
}