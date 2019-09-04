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
struct isp_ccp2_device {int dummy; } ;
struct isp_buffer {int /*<<< orphan*/  dma; } ;
struct TYPE_2__ {struct isp_ccp2_device isp_ccp2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccp2_set_inaddr (struct isp_ccp2_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccp2_video_queue(struct isp_video *video, struct isp_buffer *buffer)
{
	struct isp_ccp2_device *ccp2 = &video->isp->isp_ccp2;

	ccp2_set_inaddr(ccp2, buffer->dma);
	return 0;
}