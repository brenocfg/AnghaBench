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
struct v4l2_subdev {int /*<<< orphan*/  name; int /*<<< orphan*/  entity; } ;
struct isp_video {int dmaqueue_flags; } ;
struct isp_res_device {int state; int /*<<< orphan*/  stopping; int /*<<< orphan*/  wait; int /*<<< orphan*/  input; struct isp_video video_out; } ;
struct isp_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
#define  ISP_PIPELINE_STREAM_CONTINUOUS 130 
#define  ISP_PIPELINE_STREAM_SINGLESHOT 129 
#define  ISP_PIPELINE_STREAM_STOPPED 128 
 int ISP_VIDEO_DMAQUEUE_QUEUED ; 
 int OMAP3_ISP_SBL_RESIZER_READ ; 
 int OMAP3_ISP_SBL_RESIZER_WRITE ; 
 int /*<<< orphan*/  OMAP3_ISP_SUBCLK_RESIZER ; 
 int /*<<< orphan*/  RESIZER_INPUT_MEMORY ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_video_dmaqueue_flags_clr (struct isp_video*) ; 
 int /*<<< orphan*/  omap3isp_module_sync_idle (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap3isp_sbl_disable (struct isp_device*,int) ; 
 int /*<<< orphan*/  omap3isp_sbl_enable (struct isp_device*,int) ; 
 int /*<<< orphan*/  omap3isp_subclk_disable (struct isp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap3isp_subclk_enable (struct isp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resizer_configure (struct isp_res_device*) ; 
 int /*<<< orphan*/  resizer_enable_oneshot (struct isp_res_device*) ; 
 int /*<<< orphan*/  resizer_print_status (struct isp_res_device*) ; 
 struct device* to_device (struct isp_res_device*) ; 
 struct isp_device* to_isp_device (struct isp_res_device*) ; 
 struct isp_res_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int resizer_set_stream(struct v4l2_subdev *sd, int enable)
{
	struct isp_res_device *res = v4l2_get_subdevdata(sd);
	struct isp_video *video_out = &res->video_out;
	struct isp_device *isp = to_isp_device(res);
	struct device *dev = to_device(res);

	if (res->state == ISP_PIPELINE_STREAM_STOPPED) {
		if (enable == ISP_PIPELINE_STREAM_STOPPED)
			return 0;

		omap3isp_subclk_enable(isp, OMAP3_ISP_SUBCLK_RESIZER);
		resizer_configure(res);
		resizer_print_status(res);
	}

	switch (enable) {
	case ISP_PIPELINE_STREAM_CONTINUOUS:
		omap3isp_sbl_enable(isp, OMAP3_ISP_SBL_RESIZER_WRITE);
		if (video_out->dmaqueue_flags & ISP_VIDEO_DMAQUEUE_QUEUED) {
			resizer_enable_oneshot(res);
			isp_video_dmaqueue_flags_clr(video_out);
		}
		break;

	case ISP_PIPELINE_STREAM_SINGLESHOT:
		if (res->input == RESIZER_INPUT_MEMORY)
			omap3isp_sbl_enable(isp, OMAP3_ISP_SBL_RESIZER_READ);
		omap3isp_sbl_enable(isp, OMAP3_ISP_SBL_RESIZER_WRITE);

		resizer_enable_oneshot(res);
		break;

	case ISP_PIPELINE_STREAM_STOPPED:
		if (omap3isp_module_sync_idle(&sd->entity, &res->wait,
					      &res->stopping))
			dev_dbg(dev, "%s: module stop timeout.\n", sd->name);
		omap3isp_sbl_disable(isp, OMAP3_ISP_SBL_RESIZER_READ |
				OMAP3_ISP_SBL_RESIZER_WRITE);
		omap3isp_subclk_disable(isp, OMAP3_ISP_SUBCLK_RESIZER);
		isp_video_dmaqueue_flags_clr(video_out);
		break;
	}

	res->state = enable;
	return 0;
}