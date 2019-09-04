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
struct TYPE_2__ {int /*<<< orphan*/  entity; } ;
struct isp_prev_device {TYPE_1__ subdev; int /*<<< orphan*/  video_out; int /*<<< orphan*/  video_in; int /*<<< orphan*/  ctrls; } ;
struct isp_device {struct isp_prev_device isp_prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap3isp_video_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 

void omap3isp_preview_cleanup(struct isp_device *isp)
{
	struct isp_prev_device *prev = &isp->isp_prev;

	v4l2_ctrl_handler_free(&prev->ctrls);
	omap3isp_video_cleanup(&prev->video_in);
	omap3isp_video_cleanup(&prev->video_out);
	media_entity_cleanup(&prev->subdev.entity);
}