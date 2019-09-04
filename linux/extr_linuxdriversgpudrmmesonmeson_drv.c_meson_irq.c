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
struct meson_drm {scalar_t__ io_base; } ;
struct drm_device {struct meson_drm* dev_private; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  VENC_INTFLAG ; 
 scalar_t__ _REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meson_crtc_irq (struct meson_drm*) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 

__attribute__((used)) static irqreturn_t meson_irq(int irq, void *arg)
{
	struct drm_device *dev = arg;
	struct meson_drm *priv = dev->dev_private;

	(void)readl_relaxed(priv->io_base + _REG(VENC_INTFLAG));

	meson_crtc_irq(priv);

	return IRQ_HANDLED;
}