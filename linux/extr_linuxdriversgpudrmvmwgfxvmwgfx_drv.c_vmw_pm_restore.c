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
struct vmw_private {int suspend_locked; scalar_t__ enable_fb; int /*<<< orphan*/  dev; scalar_t__ suspend_state; int /*<<< orphan*/  reservation_sem; int /*<<< orphan*/  fman; } ;
struct pci_dev {int dummy; } ;
struct drm_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVGA_ID_2 ; 
 int /*<<< orphan*/  SVGA_REG_ID ; 
 int /*<<< orphan*/  __vmw_svga_enable (struct vmw_private*) ; 
 struct drm_device* pci_get_drvdata (struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 
 int /*<<< orphan*/  ttm_suspend_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_fb_on (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_fence_fifo_up (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_fifo_resource_inc (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_kms_resume (int /*<<< orphan*/ ) ; 
 struct vmw_private* vmw_priv (struct drm_device*) ; 
 int /*<<< orphan*/  vmw_read (struct vmw_private*,int /*<<< orphan*/ ) ; 
 int vmw_request_device (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_write (struct vmw_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmw_pm_restore(struct device *kdev)
{
	struct pci_dev *pdev = to_pci_dev(kdev);
	struct drm_device *dev = pci_get_drvdata(pdev);
	struct vmw_private *dev_priv = vmw_priv(dev);
	int ret;

	vmw_write(dev_priv, SVGA_REG_ID, SVGA_ID_2);
	(void) vmw_read(dev_priv, SVGA_REG_ID);

	if (dev_priv->enable_fb)
		vmw_fifo_resource_inc(dev_priv);

	ret = vmw_request_device(dev_priv);
	if (ret)
		return ret;

	if (dev_priv->enable_fb)
		__vmw_svga_enable(dev_priv);

	vmw_fence_fifo_up(dev_priv->fman);
	dev_priv->suspend_locked = false;
	ttm_suspend_unlock(&dev_priv->reservation_sem);
	if (dev_priv->suspend_state)
		vmw_kms_resume(dev_priv->dev);

	if (dev_priv->enable_fb)
		vmw_fb_on(dev_priv);

	return 0;
}