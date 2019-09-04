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
struct drm_psb_private {int /*<<< orphan*/  irqmask_lock; } ;
struct drm_device {scalar_t__ dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  mid_disable_pipe_event (struct drm_psb_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psb_irq_turn_off_dpst (struct drm_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int psb_irq_disable_dpst(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv =
	    (struct drm_psb_private *) dev->dev_private;
	unsigned long irqflags;

	spin_lock_irqsave(&dev_priv->irqmask_lock, irqflags);

	mid_disable_pipe_event(dev_priv, 0);
	psb_irq_turn_off_dpst(dev);

	spin_unlock_irqrestore(&dev_priv->irqmask_lock, irqflags);

	return 0;
}