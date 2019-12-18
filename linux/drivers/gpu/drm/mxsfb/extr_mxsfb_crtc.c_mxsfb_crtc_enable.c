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
struct mxsfb_drm_private {TYPE_1__* devdata; scalar_t__ base; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {scalar_t__ next_buf; scalar_t__ cur_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  mxsfb_crtc_mode_set_nofb (struct mxsfb_drm_private*) ; 
 int /*<<< orphan*/  mxsfb_enable_axi_clk (struct mxsfb_drm_private*) ; 
 int /*<<< orphan*/  mxsfb_enable_controller (struct mxsfb_drm_private*) ; 
 scalar_t__ mxsfb_get_fb_paddr (struct mxsfb_drm_private*) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

void mxsfb_crtc_enable(struct mxsfb_drm_private *mxsfb)
{
	dma_addr_t paddr;

	mxsfb_enable_axi_clk(mxsfb);
	mxsfb_crtc_mode_set_nofb(mxsfb);

	/* Write cur_buf as well to avoid an initial corrupt frame */
	paddr = mxsfb_get_fb_paddr(mxsfb);
	if (paddr) {
		writel(paddr, mxsfb->base + mxsfb->devdata->cur_buf);
		writel(paddr, mxsfb->base + mxsfb->devdata->next_buf);
	}

	mxsfb_enable_controller(mxsfb);
}