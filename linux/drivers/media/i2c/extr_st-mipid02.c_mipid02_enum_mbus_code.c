#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_mbus_code_enum {int pad; size_t index; int /*<<< orphan*/  code; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  code; } ;
struct mipid02_dev {TYPE_1__ fmt; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
#define  MIPID02_SINK_0 129 
#define  MIPID02_SOURCE 128 
 int /*<<< orphan*/ * mipid02_supported_fmt_codes ; 
 int /*<<< orphan*/  serial_to_parallel_code (int /*<<< orphan*/ ) ; 
 struct mipid02_dev* to_mipid02_dev (struct v4l2_subdev*) ; 

__attribute__((used)) static int mipid02_enum_mbus_code(struct v4l2_subdev *sd,
				 struct v4l2_subdev_pad_config *cfg,
				 struct v4l2_subdev_mbus_code_enum *code)
{
	struct mipid02_dev *bridge = to_mipid02_dev(sd);
	int ret = 0;

	switch (code->pad) {
	case MIPID02_SINK_0:
		if (code->index >= ARRAY_SIZE(mipid02_supported_fmt_codes))
			ret = -EINVAL;
		else
			code->code = mipid02_supported_fmt_codes[code->index];
		break;
	case MIPID02_SOURCE:
		if (code->index == 0)
			code->code = serial_to_parallel_code(bridge->fmt.code);
		else
			ret = -EINVAL;
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}