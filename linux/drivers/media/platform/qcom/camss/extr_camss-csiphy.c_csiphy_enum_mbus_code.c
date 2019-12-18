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
struct v4l2_subdev_mbus_code_enum {scalar_t__ pad; size_t index; int /*<<< orphan*/  code; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  code; } ;
struct csiphy_device {size_t nformats; TYPE_1__* formats; } ;
struct TYPE_2__ {int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MSM_CSIPHY_PAD_SINK ; 
 struct v4l2_mbus_framefmt* __csiphy_get_format (struct csiphy_device*,struct v4l2_subdev_pad_config*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct csiphy_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int csiphy_enum_mbus_code(struct v4l2_subdev *sd,
				 struct v4l2_subdev_pad_config *cfg,
				 struct v4l2_subdev_mbus_code_enum *code)
{
	struct csiphy_device *csiphy = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;

	if (code->pad == MSM_CSIPHY_PAD_SINK) {
		if (code->index >= csiphy->nformats)
			return -EINVAL;

		code->code = csiphy->formats[code->index].code;
	} else {
		if (code->index > 0)
			return -EINVAL;

		format = __csiphy_get_format(csiphy, cfg, MSM_CSIPHY_PAD_SINK,
					     code->which);

		code->code = format->code;
	}

	return 0;
}