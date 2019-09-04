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
struct isp_pipeline {int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  entity; } ;
struct isp_ccp2_device {scalar_t__ state; int /*<<< orphan*/  video_in; TYPE_1__ subdev; } ;
struct isp_buffer {int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_PIPELINE_IDLE_INPUT ; 
 scalar_t__ ISP_PIPELINE_STREAM_SINGLESHOT ; 
 int /*<<< orphan*/  ccp2_set_inaddr (struct isp_ccp2_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ isp_pipeline_ready (struct isp_pipeline*) ; 
 int /*<<< orphan*/  omap3isp_pipeline_set_stream (struct isp_pipeline*,scalar_t__) ; 
 struct isp_buffer* omap3isp_video_buffer_next (int /*<<< orphan*/ *) ; 
 struct isp_pipeline* to_isp_pipeline (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ccp2_isr_buffer(struct isp_ccp2_device *ccp2)
{
	struct isp_pipeline *pipe = to_isp_pipeline(&ccp2->subdev.entity);
	struct isp_buffer *buffer;

	buffer = omap3isp_video_buffer_next(&ccp2->video_in);
	if (buffer != NULL)
		ccp2_set_inaddr(ccp2, buffer->dma);

	pipe->state |= ISP_PIPELINE_IDLE_INPUT;

	if (ccp2->state == ISP_PIPELINE_STREAM_SINGLESHOT) {
		if (isp_pipeline_ready(pipe))
			omap3isp_pipeline_set_stream(pipe,
						ISP_PIPELINE_STREAM_SINGLESHOT);
	}
}