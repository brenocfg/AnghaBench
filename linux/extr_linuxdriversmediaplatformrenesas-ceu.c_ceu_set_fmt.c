#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  code; } ;
struct v4l2_subdev_format {TYPE_2__ format; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  pix_mp; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct ceu_subdev {struct v4l2_subdev* v4l2_sd; } ;
struct ceu_device {int /*<<< orphan*/  field; int /*<<< orphan*/  v4l2_pix; struct ceu_subdev* sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int __ceu_try_fmt (struct ceu_device*,struct v4l2_format*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pad ; 
 int /*<<< orphan*/  set_fmt ; 
 int /*<<< orphan*/  v4l2_fill_mbus_format_mplane (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_format*) ; 

__attribute__((used)) static int ceu_set_fmt(struct ceu_device *ceudev, struct v4l2_format *v4l2_fmt)
{
	struct ceu_subdev *ceu_sd = ceudev->sd;
	struct v4l2_subdev *v4l2_sd = ceu_sd->v4l2_sd;
	u32 mbus_code;
	int ret;

	/*
	 * Set format on sensor sub device: bus format used to produce memory
	 * format is selected at initialization time.
	 */
	struct v4l2_subdev_format format = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};

	ret = __ceu_try_fmt(ceudev, v4l2_fmt, &mbus_code);
	if (ret)
		return ret;

	format.format.code = mbus_code;
	v4l2_fill_mbus_format_mplane(&format.format, &v4l2_fmt->fmt.pix_mp);
	ret = v4l2_subdev_call(v4l2_sd, pad, set_fmt, NULL, &format);
	if (ret)
		return ret;

	ceudev->v4l2_pix = v4l2_fmt->fmt.pix_mp;
	ceudev->field = V4L2_FIELD_NONE;

	return 0;
}