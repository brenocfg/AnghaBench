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
struct drm_psb_private {int apm_base; int apm_reg; int ospm_base; int display_power; int suspended; TYPE_1__* ops; scalar_t__ display_count; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* init_pm ) (struct drm_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  power_ctrl_lock ; 
 int /*<<< orphan*/  power_mutex ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct drm_device*) ; 

void gma_power_init(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;

	/* FIXME: Move APM/OSPM base into relevant device code */
	dev_priv->apm_base = dev_priv->apm_reg & 0xffff;
	dev_priv->ospm_base &= 0xffff;

	dev_priv->display_power = true;	/* We start active */
	dev_priv->display_count = 0;	/* Currently no users */
	dev_priv->suspended = false;	/* And not suspended */
	spin_lock_init(&power_ctrl_lock);
	mutex_init(&power_mutex);

	if (dev_priv->ops->init_pm)
		dev_priv->ops->init_pm(dev);
}