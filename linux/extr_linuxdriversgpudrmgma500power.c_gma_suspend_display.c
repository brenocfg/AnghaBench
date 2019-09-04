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
struct drm_psb_private {int display_power; TYPE_1__* ops; scalar_t__ suspended; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* power_down ) (struct drm_device*) ;int /*<<< orphan*/  (* save_regs ) (struct drm_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct drm_device*) ; 
 int /*<<< orphan*/  stub2 (struct drm_device*) ; 

__attribute__((used)) static void gma_suspend_display(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;

	if (dev_priv->suspended)
		return;
	dev_priv->ops->save_regs(dev);
	dev_priv->ops->power_down(dev);
	dev_priv->display_power = false;
}