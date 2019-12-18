#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  crtc; } ;
struct tve200_drm_dev_private {scalar_t__ regs; TYPE_2__* drm; TYPE_1__ pipe; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ TVE200_CTRL ; 
 scalar_t__ TVE200_INT_CLR ; 
 scalar_t__ TVE200_INT_STAT ; 
 int TVE200_INT_V_STATUS ; 
 int TVE200_VSTSTYPE_BITS ; 
 int TVE200_VSTSTYPE_VAI ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  drm_crtc_handle_vblank (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

irqreturn_t tve200_irq(int irq, void *data)
{
	struct tve200_drm_dev_private *priv = data;
	u32 stat;
	u32 val;

	stat = readl(priv->regs + TVE200_INT_STAT);

	if (!stat)
		return IRQ_NONE;

	/*
	 * Vblank IRQ
	 *
	 * The hardware is a bit tilted: the line stays high after clearing
	 * the vblank IRQ, firing many more interrupts. We counter this
	 * by toggling the IRQ back and forth from firing at vblank and
	 * firing at start of active image, which works around the problem
	 * since those occur strictly in sequence, and we get two IRQs for each
	 * frame, one at start of Vblank (that we make call into the CRTC) and
	 * another one at the start of the image (that we discard).
	 */
	if (stat & TVE200_INT_V_STATUS) {
		val = readl(priv->regs + TVE200_CTRL);
		/* We have an actual start of vsync */
		if (!(val & TVE200_VSTSTYPE_BITS)) {
			drm_crtc_handle_vblank(&priv->pipe.crtc);
			/* Toggle trigger to start of active image */
			val |= TVE200_VSTSTYPE_VAI;
		} else {
			/* Toggle trigger back to start of vsync */
			val &= ~TVE200_VSTSTYPE_BITS;
		}
		writel(val, priv->regs + TVE200_CTRL);
	} else
		dev_err(priv->drm->dev, "stray IRQ %08x\n", stat);

	/* Clear the interrupt once done */
	writel(stat, priv->regs + TVE200_INT_CLR);

	return IRQ_HANDLED;
}