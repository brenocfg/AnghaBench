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
struct mtk_ddp_comp {scalar_t__ regs; } ;
struct mtk_disp_ovl {int /*<<< orphan*/  crtc; struct mtk_ddp_comp ddp_comp; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ DISP_REG_OVL_INTSTA ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  mtk_crtc_ddp_irq (int /*<<< orphan*/ ,struct mtk_ddp_comp*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t mtk_disp_ovl_irq_handler(int irq, void *dev_id)
{
	struct mtk_disp_ovl *priv = dev_id;
	struct mtk_ddp_comp *ovl = &priv->ddp_comp;

	/* Clear frame completion interrupt */
	writel(0x0, ovl->regs + DISP_REG_OVL_INTSTA);

	if (!priv->crtc)
		return IRQ_NONE;

	mtk_crtc_ddp_irq(priv->crtc, ovl);

	return IRQ_HANDLED;
}