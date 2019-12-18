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
struct isp_video {scalar_t__ type; TYPE_1__* isp; } ;
struct isp_res_device {int dummy; } ;
struct isp_buffer {int /*<<< orphan*/  dma; } ;
struct TYPE_2__ {struct isp_res_device isp_res; } ;

/* Variables and functions */
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  resizer_set_inaddr (struct isp_res_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resizer_set_outaddr (struct isp_res_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int resizer_video_queue(struct isp_video *video,
			       struct isp_buffer *buffer)
{
	struct isp_res_device *res = &video->isp->isp_res;

	if (video->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		resizer_set_inaddr(res, buffer->dma);

	/*
	 * We now have a buffer queued on the output. Despite what the
	 * TRM says, the resizer can't be restarted immediately.
	 * Enabling it in one shot mode in the middle of a frame (or at
	 * least asynchronously to the frame) results in the output
	 * being shifted randomly left/right and up/down, as if the
	 * hardware didn't synchronize itself to the beginning of the
	 * frame correctly.
	 *
	 * Restart the resizer on the next sync interrupt if running in
	 * continuous mode or when starting the stream.
	 */
	if (video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		resizer_set_outaddr(res, buffer->dma);

	return 0;
}