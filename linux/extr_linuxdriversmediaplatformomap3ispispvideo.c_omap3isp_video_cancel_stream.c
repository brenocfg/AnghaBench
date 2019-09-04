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
struct isp_video {int error; int /*<<< orphan*/  irqlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  omap3isp_video_return_buffers (struct isp_video*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void omap3isp_video_cancel_stream(struct isp_video *video)
{
	unsigned long flags;

	spin_lock_irqsave(&video->irqlock, flags);
	omap3isp_video_return_buffers(video, VB2_BUF_STATE_ERROR);
	video->error = true;
	spin_unlock_irqrestore(&video->irqlock, flags);
}