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
struct v4l2_mbus_framefmt {int dummy; } ;
struct isp_res_device {int /*<<< orphan*/  lock; scalar_t__ applycrop; int /*<<< orphan*/  stopping; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESZ_PAD_SINK ; 
 int /*<<< orphan*/  RESZ_PAD_SOURCE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 struct v4l2_mbus_framefmt* __resizer_get_format (struct isp_res_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ omap3isp_module_sync_is_stopping (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resizer_isr_buffer (struct isp_res_device*) ; 
 int /*<<< orphan*/  resizer_set_crop_params (struct isp_res_device*,struct v4l2_mbus_framefmt*,struct v4l2_mbus_framefmt*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void omap3isp_resizer_isr(struct isp_res_device *res)
{
	struct v4l2_mbus_framefmt *informat, *outformat;
	unsigned long flags;

	if (omap3isp_module_sync_is_stopping(&res->wait, &res->stopping))
		return;

	spin_lock_irqsave(&res->lock, flags);

	if (res->applycrop) {
		outformat = __resizer_get_format(res, NULL, RESZ_PAD_SOURCE,
					      V4L2_SUBDEV_FORMAT_ACTIVE);
		informat = __resizer_get_format(res, NULL, RESZ_PAD_SINK,
					      V4L2_SUBDEV_FORMAT_ACTIVE);
		resizer_set_crop_params(res, informat, outformat);
		res->applycrop = 0;
	}

	spin_unlock_irqrestore(&res->lock, flags);

	resizer_isr_buffer(res);
}