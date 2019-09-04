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

/* Variables and functions */
 int /*<<< orphan*/  noon010_base_regs ; 
 int noon010_bulk_write_reg (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int noon010_set_flip (struct v4l2_subdev*,int,int /*<<< orphan*/ ) ; 
 int noon010_set_params (struct v4l2_subdev*) ; 

__attribute__((used)) static int noon010_base_config(struct v4l2_subdev *sd)
{
	int ret = noon010_bulk_write_reg(sd, noon010_base_regs);
	if (!ret)
		ret = noon010_set_params(sd);
	if (!ret)
		ret = noon010_set_flip(sd, 1, 0);

	return ret;
}