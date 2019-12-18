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
struct pl111_drm_dev_private {scalar_t__ regs; TYPE_1__ pipe; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int CLCD_IRQ_NEXTBASE_UPDATE ; 
 scalar_t__ CLCD_PL111_ICR ; 
 scalar_t__ CLCD_PL111_MIS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  drm_crtc_handle_vblank (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

irqreturn_t pl111_irq(int irq, void *data)
{
	struct pl111_drm_dev_private *priv = data;
	u32 irq_stat;
	irqreturn_t status = IRQ_NONE;

	irq_stat = readl(priv->regs + CLCD_PL111_MIS);

	if (!irq_stat)
		return IRQ_NONE;

	if (irq_stat & CLCD_IRQ_NEXTBASE_UPDATE) {
		drm_crtc_handle_vblank(&priv->pipe.crtc);

		status = IRQ_HANDLED;
	}

	/* Clear the interrupt once done */
	writel(irq_stat, priv->regs + CLCD_PL111_ICR);

	return status;
}