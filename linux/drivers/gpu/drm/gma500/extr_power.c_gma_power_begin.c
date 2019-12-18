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
struct drm_psb_private {int /*<<< orphan*/  display_count; scalar_t__ display_power; } ;
struct drm_device {TYPE_1__* pdev; struct drm_psb_private* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int gma_resume_pci (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  power_ctrl_lock ; 
 int /*<<< orphan*/  psb_irq_postinstall (struct drm_device*) ; 
 int /*<<< orphan*/  psb_irq_preinstall (struct drm_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

bool gma_power_begin(struct drm_device *dev, bool force_on)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	int ret;
	unsigned long flags;

	spin_lock_irqsave(&power_ctrl_lock, flags);
	/* Power already on ? */
	if (dev_priv->display_power) {
		dev_priv->display_count++;
		pm_runtime_get(&dev->pdev->dev);
		spin_unlock_irqrestore(&power_ctrl_lock, flags);
		return true;
	}
	if (force_on == false)
		goto out_false;

	/* Ok power up needed */
	ret = gma_resume_pci(dev->pdev);
	if (ret == 0) {
		psb_irq_preinstall(dev);
		psb_irq_postinstall(dev);
		pm_runtime_get(&dev->pdev->dev);
		dev_priv->display_count++;
		spin_unlock_irqrestore(&power_ctrl_lock, flags);
		return true;
	}
out_false:
	spin_unlock_irqrestore(&power_ctrl_lock, flags);
	return false;
}