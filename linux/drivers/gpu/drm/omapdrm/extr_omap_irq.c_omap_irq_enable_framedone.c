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
struct omap_drm_private {int irq_mask; int /*<<< orphan*/  wait_lock; int /*<<< orphan*/  dispc; TYPE_1__* dispc_ops; } ;
struct drm_device {struct omap_drm_private* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;
struct TYPE_2__ {int (* mgr_get_framedone_irq ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,struct drm_device*,int,int) ; 
 int omap_crtc_channel (struct drm_crtc*) ; 
 int /*<<< orphan*/  omap_irq_update (struct drm_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

int omap_irq_enable_framedone(struct drm_crtc *crtc, bool enable)
{
	struct drm_device *dev = crtc->dev;
	struct omap_drm_private *priv = dev->dev_private;
	unsigned long flags;
	enum omap_channel channel = omap_crtc_channel(crtc);
	int framedone_irq =
		priv->dispc_ops->mgr_get_framedone_irq(priv->dispc, channel);

	DBG("dev=%p, crtc=%u, enable=%d", dev, channel, enable);

	spin_lock_irqsave(&priv->wait_lock, flags);
	if (enable)
		priv->irq_mask |= framedone_irq;
	else
		priv->irq_mask &= ~framedone_irq;
	omap_irq_update(dev);
	spin_unlock_irqrestore(&priv->wait_lock, flags);

	return 0;
}