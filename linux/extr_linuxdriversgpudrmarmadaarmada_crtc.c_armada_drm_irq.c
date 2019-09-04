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
struct armada_crtc {int irq_ena; int /*<<< orphan*/  crtc; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int DUMB_FRAMEDONE ; 
 int GRA_FRAME_IRQ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ LCD_SPU_IRQ_ISR ; 
 int VSYNC_IRQ ; 
 int /*<<< orphan*/  armada_drm_crtc_irq (struct armada_crtc*,int) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  trace_armada_drm_irq (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t armada_drm_irq(int irq, void *arg)
{
	struct armada_crtc *dcrtc = arg;
	u32 v, stat = readl_relaxed(dcrtc->base + LCD_SPU_IRQ_ISR);

	/*
	 * Reading the ISR appears to clear bits provided CLEAN_SPU_IRQ_ISR
	 * is set.  Writing has some other effect to acknowledge the IRQ -
	 * without this, we only get a single IRQ.
	 */
	writel_relaxed(0, dcrtc->base + LCD_SPU_IRQ_ISR);

	trace_armada_drm_irq(&dcrtc->crtc, stat);

	/* Mask out those interrupts we haven't enabled */
	v = stat & dcrtc->irq_ena;

	if (v & (VSYNC_IRQ|GRA_FRAME_IRQ|DUMB_FRAMEDONE)) {
		armada_drm_crtc_irq(dcrtc, stat);
		return IRQ_HANDLED;
	}
	return IRQ_NONE;
}