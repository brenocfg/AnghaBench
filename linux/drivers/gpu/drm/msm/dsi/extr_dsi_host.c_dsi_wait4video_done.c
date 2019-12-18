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
typedef  scalar_t__ u32 ;
struct msm_dsi_host {int /*<<< orphan*/  video_comp; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*) ; 
 int /*<<< orphan*/  DSI_IRQ_MASK_VIDEO_DONE ; 
 int /*<<< orphan*/  dsi_intr_ctrl (struct msm_dsi_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsi_wait4video_done(struct msm_dsi_host *msm_host)
{
	u32 ret = 0;
	struct device *dev = &msm_host->pdev->dev;

	dsi_intr_ctrl(msm_host, DSI_IRQ_MASK_VIDEO_DONE, 1);

	reinit_completion(&msm_host->video_comp);

	ret = wait_for_completion_timeout(&msm_host->video_comp,
			msecs_to_jiffies(70));

	if (ret == 0)
		DRM_DEV_ERROR(dev, "wait for video done timed out\n");

	dsi_intr_ctrl(msm_host, DSI_IRQ_MASK_VIDEO_DONE, 0);
}