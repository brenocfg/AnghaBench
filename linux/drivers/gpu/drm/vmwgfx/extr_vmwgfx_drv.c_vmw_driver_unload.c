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
struct TYPE_2__ {scalar_t__ staged_bindings; int /*<<< orphan*/  cmd_bounce; int /*<<< orphan*/  res_ht; scalar_t__ res_ht_initialized; } ;
struct vmw_private {int capabilities; int /*<<< orphan*/ * res_idr; TYPE_1__ ctx; int /*<<< orphan*/  mmio_virt; int /*<<< orphan*/  tdev; scalar_t__ stealth; int /*<<< orphan*/  dev; int /*<<< orphan*/  fman; int /*<<< orphan*/  bdev; scalar_t__ has_mob; scalar_t__ has_gmr; scalar_t__ enable_fb; int /*<<< orphan*/  pm_nb; } ;
struct drm_device {int /*<<< orphan*/  pdev; } ;
typedef  enum vmw_res_type { ____Placeholder_vmw_res_type } vmw_res_type ;

/* Variables and functions */
 int SVGA_CAP_IRQMASK ; 
 int /*<<< orphan*/  TTM_PL_VRAM ; 
 int /*<<< orphan*/  VMW_PL_GMR ; 
 int /*<<< orphan*/  VMW_PL_MOB ; 
 int /*<<< orphan*/  drm_ht_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vmw_private*) ; 
 int /*<<< orphan*/  memunmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_clean_mm (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_device_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_object_device_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_pm_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_binding_state_free (scalar_t__) ; 
 int /*<<< orphan*/  vmw_fb_close (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_fb_off (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_fence_manager_takedown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_fifo_resource_dec (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_irq_uninstall (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_kms_close (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_overlay_close (struct vmw_private*) ; 
 struct vmw_private* vmw_priv (struct drm_device*) ; 
 int /*<<< orphan*/  vmw_release_device_early (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_release_device_late (struct vmw_private*) ; 
 int vmw_res_context ; 
 int vmw_res_max ; 
 int /*<<< orphan*/  vmw_svga_disable (struct vmw_private*) ; 

__attribute__((used)) static void vmw_driver_unload(struct drm_device *dev)
{
	struct vmw_private *dev_priv = vmw_priv(dev);
	enum vmw_res_type i;

	unregister_pm_notifier(&dev_priv->pm_nb);

	if (dev_priv->ctx.res_ht_initialized)
		drm_ht_remove(&dev_priv->ctx.res_ht);
	vfree(dev_priv->ctx.cmd_bounce);
	if (dev_priv->enable_fb) {
		vmw_fb_off(dev_priv);
		vmw_fb_close(dev_priv);
		vmw_fifo_resource_dec(dev_priv);
		vmw_svga_disable(dev_priv);
	}

	vmw_kms_close(dev_priv);
	vmw_overlay_close(dev_priv);

	if (dev_priv->has_gmr)
		(void)ttm_bo_clean_mm(&dev_priv->bdev, VMW_PL_GMR);
	(void)ttm_bo_clean_mm(&dev_priv->bdev, TTM_PL_VRAM);

	vmw_release_device_early(dev_priv);
	if (dev_priv->has_mob)
		(void) ttm_bo_clean_mm(&dev_priv->bdev, VMW_PL_MOB);
	(void) ttm_bo_device_release(&dev_priv->bdev);
	vmw_release_device_late(dev_priv);
	vmw_fence_manager_takedown(dev_priv->fman);
	if (dev_priv->capabilities & SVGA_CAP_IRQMASK)
		vmw_irq_uninstall(dev_priv->dev);
	if (dev_priv->stealth)
		pci_release_region(dev->pdev, 2);
	else
		pci_release_regions(dev->pdev);

	ttm_object_device_release(&dev_priv->tdev);
	memunmap(dev_priv->mmio_virt);
	if (dev_priv->ctx.staged_bindings)
		vmw_binding_state_free(dev_priv->ctx.staged_bindings);

	for (i = vmw_res_context; i < vmw_res_max; ++i)
		idr_destroy(&dev_priv->res_idr[i]);

	kfree(dev_priv);
}