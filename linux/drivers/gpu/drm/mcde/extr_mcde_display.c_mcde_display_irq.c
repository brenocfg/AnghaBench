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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  crtc; } ;
struct mcde {scalar_t__ flow_active; scalar_t__ regs; int /*<<< orphan*/  dev; TYPE_1__ pipe; int /*<<< orphan*/  flow_lock; scalar_t__ oneshot_mode; int /*<<< orphan*/  mdsi; } ;

/* Variables and functions */
 scalar_t__ MCDE_CRA0 ; 
 int MCDE_CRX0_FLOEN ; 
 scalar_t__ MCDE_MISCHNL ; 
 scalar_t__ MCDE_MISOVL ; 
 scalar_t__ MCDE_MISPP ; 
 int MCDE_PP_VCMPA ; 
 int MCDE_PP_VCMPB ; 
 int MCDE_PP_VCMPC0 ; 
 int MCDE_PP_VCMPC1 ; 
 int MCDE_PP_VSCC0 ; 
 int MCDE_PP_VSCC1 ; 
 scalar_t__ MCDE_RISCHNL ; 
 scalar_t__ MCDE_RISOVL ; 
 scalar_t__ MCDE_RISPP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  drm_crtc_handle_vblank (int /*<<< orphan*/ *) ; 
 scalar_t__ mcde_dsi_irq (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void mcde_display_irq(struct mcde *mcde)
{
	u32 mispp, misovl, mischnl;
	bool vblank = false;

	/* Handle display IRQs */
	mispp = readl(mcde->regs + MCDE_MISPP);
	misovl = readl(mcde->regs + MCDE_MISOVL);
	mischnl = readl(mcde->regs + MCDE_MISCHNL);

	/*
	 * Handle IRQs from the DSI link. All IRQs from the DSI links
	 * are just latched onto the MCDE IRQ line, so we need to traverse
	 * any active DSI masters and check if an IRQ is originating from
	 * them.
	 *
	 * TODO: Currently only one DSI link is supported.
	 */
	if (mcde_dsi_irq(mcde->mdsi)) {
		u32 val;

		/*
		 * In oneshot mode we do not send continuous updates
		 * to the display, instead we only push out updates when
		 * the update function is called, then we disable the
		 * flow on the channel once we get the TE IRQ.
		 */
		if (mcde->oneshot_mode) {
			spin_lock(&mcde->flow_lock);
			if (--mcde->flow_active == 0) {
				dev_dbg(mcde->dev, "TE0 IRQ\n");
				/* Disable FIFO A flow */
				val = readl(mcde->regs + MCDE_CRA0);
				val &= ~MCDE_CRX0_FLOEN;
				writel(val, mcde->regs + MCDE_CRA0);
			}
			spin_unlock(&mcde->flow_lock);
		}
	}

	/* Vblank from one of the channels */
	if (mispp & MCDE_PP_VCMPA) {
		dev_dbg(mcde->dev, "chnl A vblank IRQ\n");
		vblank = true;
	}
	if (mispp & MCDE_PP_VCMPB) {
		dev_dbg(mcde->dev, "chnl B vblank IRQ\n");
		vblank = true;
	}
	if (mispp & MCDE_PP_VCMPC0)
		dev_dbg(mcde->dev, "chnl C0 vblank IRQ\n");
	if (mispp & MCDE_PP_VCMPC1)
		dev_dbg(mcde->dev, "chnl C1 vblank IRQ\n");
	if (mispp & MCDE_PP_VSCC0)
		dev_dbg(mcde->dev, "chnl C0 TE IRQ\n");
	if (mispp & MCDE_PP_VSCC1)
		dev_dbg(mcde->dev, "chnl C1 TE IRQ\n");
	writel(mispp, mcde->regs + MCDE_RISPP);

	if (vblank)
		drm_crtc_handle_vblank(&mcde->pipe.crtc);

	if (misovl)
		dev_info(mcde->dev, "some stray overlay IRQ %08x\n", misovl);
	writel(misovl, mcde->regs + MCDE_RISOVL);

	if (mischnl)
		dev_info(mcde->dev, "some stray channel error IRQ %08x\n",
			 mischnl);
	writel(mischnl, mcde->regs + MCDE_RISCHNL);
}