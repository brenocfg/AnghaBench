#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev_format {int /*<<< orphan*/  format; int /*<<< orphan*/  which; } ;
struct TYPE_5__ {int /*<<< orphan*/  pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct TYPE_8__ {scalar_t__ sd_format; } ;
struct TYPE_7__ {int /*<<< orphan*/  hist_stat; } ;
struct isc_device {int /*<<< orphan*/  v4l2_dev; TYPE_4__ try_config; TYPE_4__ config; TYPE_3__ ctrls; struct v4l2_format fmt; TYPE_2__* current_subdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIST_INIT ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  isc_reset_awb_ctrls (struct isc_device*) ; 
 int isc_try_fmt (struct isc_device*,struct v4l2_format*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pad ; 
 int /*<<< orphan*/  set_fmt ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_fill_mbus_format (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_format*) ; 

__attribute__((used)) static int isc_set_fmt(struct isc_device *isc, struct v4l2_format *f)
{
	struct v4l2_subdev_format format = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};
	u32 mbus_code = 0;
	int ret;

	ret = isc_try_fmt(isc, f, &mbus_code);
	if (ret)
		return ret;

	v4l2_fill_mbus_format(&format.format, &f->fmt.pix, mbus_code);
	ret = v4l2_subdev_call(isc->current_subdev->sd, pad,
			       set_fmt, NULL, &format);
	if (ret < 0)
		return ret;

	isc->fmt = *f;

	if (isc->try_config.sd_format && isc->config.sd_format &&
	    isc->try_config.sd_format != isc->config.sd_format) {
		isc->ctrls.hist_stat = HIST_INIT;
		isc_reset_awb_ctrls(isc);
	}
	/* make the try configuration active */
	isc->config = isc->try_config;

	v4l2_dbg(1, debug, &isc->v4l2_dev, "New ISC configuration in place\n");

	return 0;
}