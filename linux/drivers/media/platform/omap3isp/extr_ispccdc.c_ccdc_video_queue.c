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
struct isp_video {TYPE_1__* isp; } ;
struct isp_ccdc_device {int output; scalar_t__ state; int underrun; int /*<<< orphan*/  lock; scalar_t__ bt656; int /*<<< orphan*/  running; } ;
struct isp_buffer {int /*<<< orphan*/  dma; } ;
struct TYPE_2__ {struct isp_ccdc_device isp_ccdc; } ;

/* Variables and functions */
 int CCDC_OUTPUT_MEMORY ; 
 int ENODEV ; 
 scalar_t__ ISP_PIPELINE_STREAM_CONTINUOUS ; 
 int /*<<< orphan*/  ccdc_enable (struct isp_ccdc_device*) ; 
 int /*<<< orphan*/  ccdc_set_outaddr (struct isp_ccdc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ccdc_video_queue(struct isp_video *video, struct isp_buffer *buffer)
{
	struct isp_ccdc_device *ccdc = &video->isp->isp_ccdc;
	unsigned long flags;
	bool restart = false;

	if (!(ccdc->output & CCDC_OUTPUT_MEMORY))
		return -ENODEV;

	ccdc_set_outaddr(ccdc, buffer->dma);

	/* We now have a buffer queued on the output, restart the pipeline
	 * on the next CCDC interrupt if running in continuous mode (or when
	 * starting the stream) in external sync mode, or immediately in BT.656
	 * sync mode as no CCDC interrupt is generated when the CCDC is stopped
	 * in that case.
	 */
	spin_lock_irqsave(&ccdc->lock, flags);
	if (ccdc->state == ISP_PIPELINE_STREAM_CONTINUOUS && !ccdc->running &&
	    ccdc->bt656)
		restart = true;
	else
		ccdc->underrun = 1;
	spin_unlock_irqrestore(&ccdc->lock, flags);

	if (restart)
		ccdc_enable(ccdc);

	return 0;
}