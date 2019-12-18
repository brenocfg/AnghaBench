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
struct isp_video {struct isp_device* isp; } ;
struct TYPE_2__ {int dmaqueue_flags; } ;
struct isp_csi2_device {TYPE_1__ video_out; } ;
struct isp_device {struct isp_csi2_device isp_csi2a; } ;
struct isp_buffer {int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int ISP_VIDEO_DMAQUEUE_UNDERRUN ; 
 int /*<<< orphan*/  csi2_ctx_enable (struct isp_device*,struct isp_csi2_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  csi2_if_enable (struct isp_device*,struct isp_csi2_device*,int) ; 
 int /*<<< orphan*/  csi2_set_outaddr (struct isp_csi2_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_video_dmaqueue_flags_clr (TYPE_1__*) ; 

__attribute__((used)) static int csi2_queue(struct isp_video *video, struct isp_buffer *buffer)
{
	struct isp_device *isp = video->isp;
	struct isp_csi2_device *csi2 = &isp->isp_csi2a;

	csi2_set_outaddr(csi2, buffer->dma);

	/*
	 * If streaming was enabled before there was a buffer queued
	 * or underrun happened in the ISR, the hardware was not enabled
	 * and DMA queue flag ISP_VIDEO_DMAQUEUE_UNDERRUN is still set.
	 * Enable it now.
	 */
	if (csi2->video_out.dmaqueue_flags & ISP_VIDEO_DMAQUEUE_UNDERRUN) {
		/* Enable / disable context 0 and IRQs */
		csi2_if_enable(isp, csi2, 1);
		csi2_ctx_enable(isp, csi2, 0, 1);
		isp_video_dmaqueue_flags_clr(&csi2->video_out);
	}

	return 0;
}