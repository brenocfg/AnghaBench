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
struct TYPE_2__ {int dmaqueue_flags; } ;
struct isp_prev_device {scalar_t__ state; TYPE_1__ video_out; } ;

/* Variables and functions */
 scalar_t__ ISP_PIPELINE_STREAM_CONTINUOUS ; 
 int ISP_VIDEO_DMAQUEUE_QUEUED ; 
 int /*<<< orphan*/  isp_video_dmaqueue_flags_clr (TYPE_1__*) ; 
 int /*<<< orphan*/  preview_enable_oneshot (struct isp_prev_device*) ; 

void omap3isp_preview_isr_frame_sync(struct isp_prev_device *prev)
{
	/*
	 * If ISP_VIDEO_DMAQUEUE_QUEUED is set, DMA queue had an underrun
	 * condition, the module was paused and now we have a buffer queued
	 * on the output again. Restart the pipeline if running in continuous
	 * mode.
	 */
	if (prev->state == ISP_PIPELINE_STREAM_CONTINUOUS &&
	    prev->video_out.dmaqueue_flags & ISP_VIDEO_DMAQUEUE_QUEUED) {
		preview_enable_oneshot(prev);
		isp_video_dmaqueue_flags_clr(&prev->video_out);
	}
}