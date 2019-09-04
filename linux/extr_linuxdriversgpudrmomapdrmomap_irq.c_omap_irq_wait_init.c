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
typedef  int /*<<< orphan*/  u32 ;
struct omap_irq_wait {int count; int /*<<< orphan*/  node; int /*<<< orphan*/  irqmask; int /*<<< orphan*/  wq; } ;
struct omap_drm_private {int /*<<< orphan*/  wait_lock; int /*<<< orphan*/  wait_list; } ;
struct drm_device {struct omap_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct omap_irq_wait* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_irq_update (struct drm_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct omap_irq_wait * omap_irq_wait_init(struct drm_device *dev,
		u32 irqmask, int count)
{
	struct omap_drm_private *priv = dev->dev_private;
	struct omap_irq_wait *wait = kzalloc(sizeof(*wait), GFP_KERNEL);
	unsigned long flags;

	init_waitqueue_head(&wait->wq);
	wait->irqmask = irqmask;
	wait->count = count;

	spin_lock_irqsave(&priv->wait_lock, flags);
	list_add(&wait->node, &priv->wait_list);
	omap_irq_update(dev);
	spin_unlock_irqrestore(&priv->wait_lock, flags);

	return wait;
}