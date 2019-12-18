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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_mbus_code_enum {int /*<<< orphan*/  code; int /*<<< orphan*/  index; } ;
struct v4l2_subdev {int dummy; } ;
struct fimc_fmt {int /*<<< orphan*/  mbus_code; } ;

/* Variables and functions */
 int EINVAL ; 
 struct fimc_fmt* fimc_lite_find_format (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fimc_lite_subdev_enum_mbus_code(struct v4l2_subdev *sd,
					   struct v4l2_subdev_pad_config *cfg,
					   struct v4l2_subdev_mbus_code_enum *code)
{
	const struct fimc_fmt *fmt;

	fmt = fimc_lite_find_format(NULL, NULL, 0, code->index);
	if (!fmt)
		return -EINVAL;
	code->code = fmt->mbus_code;
	return 0;
}