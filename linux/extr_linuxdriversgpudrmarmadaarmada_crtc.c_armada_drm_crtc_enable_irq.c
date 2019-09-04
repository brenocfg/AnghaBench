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
struct armada_crtc {int irq_ena; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ LCD_SPU_IRQ_ENA ; 
 scalar_t__ LCD_SPU_IRQ_ISR ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void armada_drm_crtc_enable_irq(struct armada_crtc *dcrtc, u32 mask)
{
	if ((dcrtc->irq_ena & mask) != mask) {
		dcrtc->irq_ena |= mask;
		writel(dcrtc->irq_ena, dcrtc->base + LCD_SPU_IRQ_ENA);
		if (readl_relaxed(dcrtc->base + LCD_SPU_IRQ_ISR) & mask)
			writel(0, dcrtc->base + LCD_SPU_IRQ_ISR);
	}
}