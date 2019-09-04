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
struct v4l2_subdev_format {int /*<<< orphan*/  format; int /*<<< orphan*/  which; } ;
struct TYPE_3__ {int /*<<< orphan*/  pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct isc_format {int dummy; } ;
struct isc_device {struct isc_format* current_fmt; struct v4l2_format fmt; TYPE_2__* current_subdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int isc_try_fmt (struct isc_device*,struct v4l2_format*,struct isc_format**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pad ; 
 int /*<<< orphan*/  set_fmt ; 
 int /*<<< orphan*/  v4l2_fill_mbus_format (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_format*) ; 

__attribute__((used)) static int isc_set_fmt(struct isc_device *isc, struct v4l2_format *f)
{
	struct v4l2_subdev_format format = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};
	struct isc_format *current_fmt;
	u32 mbus_code;
	int ret;

	ret = isc_try_fmt(isc, f, &current_fmt, &mbus_code);
	if (ret)
		return ret;

	v4l2_fill_mbus_format(&format.format, &f->fmt.pix, mbus_code);
	ret = v4l2_subdev_call(isc->current_subdev->sd, pad,
			       set_fmt, NULL, &format);
	if (ret < 0)
		return ret;

	isc->fmt = *f;
	isc->current_fmt = current_fmt;

	return 0;
}