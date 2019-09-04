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
typedef  unsigned int u32 ;
struct v4l2_subdev_mbus_code_enum {int /*<<< orphan*/  code; int /*<<< orphan*/  index; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;
struct isc_format {int flags; int sd_support; int isc_support; } ;
struct isc_device {unsigned int num_user_formats; struct isc_format** user_formats; int /*<<< orphan*/  dev; struct isc_format* raw_fmt; TYPE_1__* current_subdev; } ;
struct TYPE_2__ {struct v4l2_subdev* sd; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct isc_format*) ; 
 int ENOMEM ; 
 int ENXIO ; 
 int FMT_FLAG_FROM_CONTROLLER ; 
 int FMT_FLAG_FROM_SENSOR ; 
 int FMT_FLAG_RAW_FORMAT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 struct isc_format** devm_kcalloc (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enum_mbus_code ; 
 struct isc_format* find_format_by_code (int /*<<< orphan*/ ,unsigned int*) ; 
 struct isc_format* formats_list ; 
 int /*<<< orphan*/  pad ; 
 int /*<<< orphan*/  v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_mbus_code_enum*) ; 

__attribute__((used)) static int isc_formats_init(struct isc_device *isc)
{
	struct isc_format *fmt;
	struct v4l2_subdev *subdev = isc->current_subdev->sd;
	unsigned int num_fmts, i, j;
	u32 list_size = ARRAY_SIZE(formats_list);
	struct v4l2_subdev_mbus_code_enum mbus_code = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};

	while (!v4l2_subdev_call(subdev, pad, enum_mbus_code,
	       NULL, &mbus_code)) {
		mbus_code.index++;

		fmt = find_format_by_code(mbus_code.code, &i);
		if ((!fmt) || (!(fmt->flags & FMT_FLAG_FROM_SENSOR)))
			continue;

		fmt->sd_support = true;

		if (fmt->flags & FMT_FLAG_RAW_FORMAT)
			isc->raw_fmt = fmt;
	}

	fmt = &formats_list[0];
	for (i = 0; i < list_size; i++) {
		if (fmt->flags & FMT_FLAG_FROM_CONTROLLER)
			fmt->isc_support = true;

		fmt++;
	}

	fmt = &formats_list[0];
	num_fmts = 0;
	for (i = 0; i < list_size; i++) {
		if (fmt->isc_support || fmt->sd_support)
			num_fmts++;

		fmt++;
	}

	if (!num_fmts)
		return -ENXIO;

	isc->num_user_formats = num_fmts;
	isc->user_formats = devm_kcalloc(isc->dev,
					 num_fmts, sizeof(*isc->user_formats),
					 GFP_KERNEL);
	if (!isc->user_formats)
		return -ENOMEM;

	fmt = &formats_list[0];
	for (i = 0, j = 0; i < list_size; i++) {
		if (fmt->isc_support || fmt->sd_support)
			isc->user_formats[j++] = fmt;

		fmt++;
	}

	return 0;
}