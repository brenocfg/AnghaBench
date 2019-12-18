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
struct isp_prev_device {int output; scalar_t__ input; int state; int /*<<< orphan*/  video_in; int /*<<< orphan*/  video_out; TYPE_1__ subdev; } ;
struct isp_pipeline {int /*<<< orphan*/  state; } ;
struct isp_buffer {int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_PIPELINE_IDLE_INPUT ; 
 int /*<<< orphan*/  ISP_PIPELINE_IDLE_OUTPUT ; 
#define  ISP_PIPELINE_STREAM_CONTINUOUS 130 
#define  ISP_PIPELINE_STREAM_SINGLESHOT 129 
#define  ISP_PIPELINE_STREAM_STOPPED 128 
 scalar_t__ PREVIEW_INPUT_MEMORY ; 
 int PREVIEW_OUTPUT_MEMORY ; 
 int /*<<< orphan*/  isp_pipeline_ready (struct isp_pipeline*) ; 
 int /*<<< orphan*/  omap3isp_pipeline_set_stream (struct isp_pipeline*,int const) ; 
 struct isp_buffer* omap3isp_video_buffer_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  preview_enable_oneshot (struct isp_prev_device*) ; 
 int /*<<< orphan*/  preview_set_inaddr (struct isp_prev_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preview_set_outaddr (struct isp_prev_device*,int /*<<< orphan*/ ) ; 
 struct isp_pipeline* to_isp_pipeline (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void preview_isr_buffer(struct isp_prev_device *prev)
{
	struct isp_pipeline *pipe = to_isp_pipeline(&prev->subdev.entity);
	struct isp_buffer *buffer;
	int restart = 0;

	if (prev->output & PREVIEW_OUTPUT_MEMORY) {
		buffer = omap3isp_video_buffer_next(&prev->video_out);
		if (buffer != NULL) {
			preview_set_outaddr(prev, buffer->dma);
			restart = 1;
		}
		pipe->state |= ISP_PIPELINE_IDLE_OUTPUT;
	}

	if (prev->input == PREVIEW_INPUT_MEMORY) {
		buffer = omap3isp_video_buffer_next(&prev->video_in);
		if (buffer != NULL)
			preview_set_inaddr(prev, buffer->dma);
		pipe->state |= ISP_PIPELINE_IDLE_INPUT;
	}

	switch (prev->state) {
	case ISP_PIPELINE_STREAM_SINGLESHOT:
		if (isp_pipeline_ready(pipe))
			omap3isp_pipeline_set_stream(pipe,
						ISP_PIPELINE_STREAM_SINGLESHOT);
		break;

	case ISP_PIPELINE_STREAM_CONTINUOUS:
		/* If an underrun occurs, the video queue operation handler will
		 * restart the preview engine. Otherwise restart it immediately.
		 */
		if (restart)
			preview_enable_oneshot(prev);
		break;

	case ISP_PIPELINE_STREAM_STOPPED:
	default:
		return;
	}
}