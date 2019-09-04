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
struct isp_device {int dummy; } ;
struct isp_csi2_device {int /*<<< orphan*/  video_out; struct isp_device* isp; } ;
struct isp_buffer {int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  csi2_ctx_enable (struct isp_device*,struct isp_csi2_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  csi2_set_outaddr (struct isp_csi2_device*,int /*<<< orphan*/ ) ; 
 struct isp_buffer* omap3isp_video_buffer_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void csi2_isr_buffer(struct isp_csi2_device *csi2)
{
	struct isp_device *isp = csi2->isp;
	struct isp_buffer *buffer;

	csi2_ctx_enable(isp, csi2, 0, 0);

	buffer = omap3isp_video_buffer_next(&csi2->video_out);

	/*
	 * Let video queue operation restart engine if there is an underrun
	 * condition.
	 */
	if (buffer == NULL)
		return;

	csi2_set_outaddr(csi2, buffer->dma);
	csi2_ctx_enable(isp, csi2, 0, 1);
}