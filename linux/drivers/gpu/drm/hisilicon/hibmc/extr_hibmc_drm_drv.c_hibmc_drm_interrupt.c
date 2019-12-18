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
struct hibmc_drm_private {scalar_t__ mmio; } ;
struct drm_device {scalar_t__ dev_private; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ HIBMC_RAW_INTERRUPT ; 
 int HIBMC_RAW_INTERRUPT_VBLANK (int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  drm_handle_vblank (struct drm_device*,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t hibmc_drm_interrupt(int irq, void *arg)
{
	struct drm_device *dev = (struct drm_device *)arg;
	struct hibmc_drm_private *priv =
		(struct hibmc_drm_private *)dev->dev_private;
	u32 status;

	status = readl(priv->mmio + HIBMC_RAW_INTERRUPT);

	if (status & HIBMC_RAW_INTERRUPT_VBLANK(1)) {
		writel(HIBMC_RAW_INTERRUPT_VBLANK(1),
		       priv->mmio + HIBMC_RAW_INTERRUPT);
		drm_handle_vblank(dev, 0);
	}

	return IRQ_HANDLED;
}