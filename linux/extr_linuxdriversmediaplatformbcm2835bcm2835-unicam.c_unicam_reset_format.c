#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_mbus_framefmt {int /*<<< orphan*/  code; } ;
struct TYPE_4__ {int /*<<< orphan*/  pix; } ;
struct TYPE_6__ {int /*<<< orphan*/  type; TYPE_1__ fmt; } ;
struct unicam_device {struct v4l2_mbus_framefmt m_fmt; TYPE_3__ v_fmt; TYPE_2__* fmt; } ;
struct TYPE_5__ {int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int __subdev_get_format (struct unicam_device*,struct v4l2_mbus_framefmt*) ; 
 int /*<<< orphan*/  unicam_calc_format_size_bpl (struct unicam_device*,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  unicam_err (struct unicam_device*,char*,int,...) ; 
 int /*<<< orphan*/  v4l2_fill_pix_format (int /*<<< orphan*/ *,struct v4l2_mbus_framefmt*) ; 

__attribute__((used)) static int unicam_reset_format(struct unicam_device *dev)
{
	struct v4l2_mbus_framefmt mbus_fmt;
	int ret;

	ret = __subdev_get_format(dev, &mbus_fmt);
	if (ret) {
		unicam_err(dev, "Failed to get_format - ret %d\n", ret);
		return ret;
	}

	if (mbus_fmt.code != dev->fmt->code) {
		unicam_err(dev, "code mismatch - fmt->code %08x, mbus_fmt.code %08x\n",
			   dev->fmt->code, mbus_fmt.code);
		return ret;
	}

	v4l2_fill_pix_format(&dev->v_fmt.fmt.pix, &mbus_fmt);
	dev->v_fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	unicam_calc_format_size_bpl(dev, dev->fmt, &dev->v_fmt);

	dev->m_fmt = mbus_fmt;

	return 0;
}