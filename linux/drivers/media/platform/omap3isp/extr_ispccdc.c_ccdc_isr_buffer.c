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
struct isp_pipeline {int /*<<< orphan*/  state; } ;
struct isp_device {int /*<<< orphan*/  crashed; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dmaqueue; } ;
struct TYPE_3__ {int /*<<< orphan*/  entity; } ;
struct isp_ccdc_device {scalar_t__ state; TYPE_2__ video_out; TYPE_1__ subdev; scalar_t__ underrun; } ;
struct isp_buffer {int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_PIPELINE_IDLE_OUTPUT ; 
 scalar_t__ ISP_PIPELINE_STREAM_CONTINUOUS ; 
 scalar_t__ ISP_PIPELINE_STREAM_SINGLESHOT ; 
 int /*<<< orphan*/  ccdc_has_all_fields (struct isp_ccdc_device*) ; 
 scalar_t__ ccdc_sbl_wait_idle (struct isp_ccdc_device*,int) ; 
 int /*<<< orphan*/  ccdc_set_outaddr (struct isp_ccdc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isp_pipeline_ready (struct isp_pipeline*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_entity_enum_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap3isp_pipeline_cancel_stream (struct isp_pipeline*) ; 
 int /*<<< orphan*/  omap3isp_pipeline_set_stream (struct isp_pipeline*,scalar_t__) ; 
 struct isp_buffer* omap3isp_video_buffer_next (TYPE_2__*) ; 
 struct isp_device* to_isp_device (struct isp_ccdc_device*) ; 
 struct isp_pipeline* to_isp_pipeline (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ccdc_isr_buffer(struct isp_ccdc_device *ccdc)
{
	struct isp_pipeline *pipe = to_isp_pipeline(&ccdc->subdev.entity);
	struct isp_device *isp = to_isp_device(ccdc);
	struct isp_buffer *buffer;

	/* The CCDC generates VD0 interrupts even when disabled (the datasheet
	 * doesn't explicitly state if that's supposed to happen or not, so it
	 * can be considered as a hardware bug or as a feature, but we have to
	 * deal with it anyway). Disabling the CCDC when no buffer is available
	 * would thus not be enough, we need to handle the situation explicitly.
	 */
	if (list_empty(&ccdc->video_out.dmaqueue))
		return 0;

	/* We're in continuous mode, and memory writes were disabled due to a
	 * buffer underrun. Re-enable them now that we have a buffer. The buffer
	 * address has been set in ccdc_video_queue.
	 */
	if (ccdc->state == ISP_PIPELINE_STREAM_CONTINUOUS && ccdc->underrun) {
		ccdc->underrun = 0;
		return 1;
	}

	/* Wait for the CCDC to become idle. */
	if (ccdc_sbl_wait_idle(ccdc, 1000)) {
		dev_info(isp->dev, "CCDC won't become idle!\n");
		media_entity_enum_set(&isp->crashed, &ccdc->subdev.entity);
		omap3isp_pipeline_cancel_stream(pipe);
		return 0;
	}

	if (!ccdc_has_all_fields(ccdc))
		return 1;

	buffer = omap3isp_video_buffer_next(&ccdc->video_out);
	if (buffer != NULL)
		ccdc_set_outaddr(ccdc, buffer->dma);

	pipe->state |= ISP_PIPELINE_IDLE_OUTPUT;

	if (ccdc->state == ISP_PIPELINE_STREAM_SINGLESHOT &&
	    isp_pipeline_ready(pipe))
		omap3isp_pipeline_set_stream(pipe,
					ISP_PIPELINE_STREAM_SINGLESHOT);

	return buffer != NULL;
}