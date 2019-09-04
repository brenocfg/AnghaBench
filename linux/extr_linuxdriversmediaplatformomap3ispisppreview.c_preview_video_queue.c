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
struct isp_prev_device {int dummy; } ;
struct isp_buffer {int /*<<< orphan*/  dma; } ;
struct TYPE_2__ {struct isp_prev_device isp_prev; } ;

/* Variables and functions */
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  preview_set_inaddr (struct isp_prev_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preview_set_outaddr (struct isp_prev_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int preview_video_queue(struct isp_video *video,
			       struct isp_buffer *buffer)
{
	struct isp_prev_device *prev = &video->isp->isp_prev;

	if (video->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		preview_set_inaddr(prev, buffer->dma);

	if (video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		preview_set_outaddr(prev, buffer->dma);

	return 0;
}