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
typedef  int u32 ;
struct vc4_crtc {int /*<<< orphan*/  base; scalar_t__ vblank_enabled; scalar_t__ regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ SMICS ; 
 int SMICS_INTERRUPTS ; 
 int /*<<< orphan*/  drm_crtc_handle_vblank (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  vc4_crtc_handle_page_flip (struct vc4_crtc*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t vc4_crtc_irq_handler(int irq, void *data)
{
	struct vc4_crtc *vc4_crtc = data;
	u32 stat = readl(vc4_crtc->regs + SMICS);
	irqreturn_t ret = IRQ_NONE;

	if (stat & SMICS_INTERRUPTS) {
		writel(0, vc4_crtc->regs + SMICS);
		if (vc4_crtc->vblank_enabled)
			drm_crtc_handle_vblank(&vc4_crtc->base);
		vc4_crtc_handle_page_flip(vc4_crtc);
		ret = IRQ_HANDLED;
	}

	return ret;
}