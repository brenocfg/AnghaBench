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
struct psb_gtt {int /*<<< orphan*/  sem; int /*<<< orphan*/  mmu_gatt_start; } ;
struct drm_psb_private {int vram_stolen_size; int /*<<< orphan*/  lpc_pdev; int /*<<< orphan*/  aux_pdev; int /*<<< orphan*/ * aux_reg; int /*<<< orphan*/ * sgx_reg; int /*<<< orphan*/ * vdc_reg; int /*<<< orphan*/ * scratch_page; int /*<<< orphan*/ * mmu; struct psb_gtt gtt; int /*<<< orphan*/ * pf_pd; TYPE_1__* ops; scalar_t__ backlight_device; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* chip_teardown ) (struct drm_device*) ;} ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gma_backlight_exit (struct drm_device*) ; 
 int /*<<< orphan*/  gma_power_uninit (struct drm_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct drm_psb_private*) ; 
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psb_gtt_takedown (struct drm_device*) ; 
 int /*<<< orphan*/  psb_intel_destroy_bios (struct drm_device*) ; 
 int /*<<< orphan*/  psb_intel_opregion_fini (struct drm_device*) ; 
 int /*<<< orphan*/  psb_mmu_driver_takedown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psb_mmu_free_pagedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psb_mmu_get_default_pd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psb_mmu_remove_pfn_sequence (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  psb_modeset_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  set_pages_wb (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct drm_device*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void psb_driver_unload(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;

	/* TODO: Kill vblank etc here */

	if (dev_priv) {
		if (dev_priv->backlight_device)
			gma_backlight_exit(dev);
		psb_modeset_cleanup(dev);

		if (dev_priv->ops->chip_teardown)
			dev_priv->ops->chip_teardown(dev);

		psb_intel_opregion_fini(dev);

		if (dev_priv->pf_pd) {
			psb_mmu_free_pagedir(dev_priv->pf_pd);
			dev_priv->pf_pd = NULL;
		}
		if (dev_priv->mmu) {
			struct psb_gtt *pg = &dev_priv->gtt;

			down_read(&pg->sem);
			psb_mmu_remove_pfn_sequence(
				psb_mmu_get_default_pd
				(dev_priv->mmu),
				pg->mmu_gatt_start,
				dev_priv->vram_stolen_size >> PAGE_SHIFT);
			up_read(&pg->sem);
			psb_mmu_driver_takedown(dev_priv->mmu);
			dev_priv->mmu = NULL;
		}
		psb_gtt_takedown(dev);
		if (dev_priv->scratch_page) {
			set_pages_wb(dev_priv->scratch_page, 1);
			__free_page(dev_priv->scratch_page);
			dev_priv->scratch_page = NULL;
		}
		if (dev_priv->vdc_reg) {
			iounmap(dev_priv->vdc_reg);
			dev_priv->vdc_reg = NULL;
		}
		if (dev_priv->sgx_reg) {
			iounmap(dev_priv->sgx_reg);
			dev_priv->sgx_reg = NULL;
		}
		if (dev_priv->aux_reg) {
			iounmap(dev_priv->aux_reg);
			dev_priv->aux_reg = NULL;
		}
		pci_dev_put(dev_priv->aux_pdev);
		pci_dev_put(dev_priv->lpc_pdev);

		/* Destroy VBT data */
		psb_intel_destroy_bios(dev);

		kfree(dev_priv);
		dev->dev_private = NULL;
	}
	gma_power_uninit(dev);
}