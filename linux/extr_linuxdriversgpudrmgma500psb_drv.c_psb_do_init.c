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
typedef  int uint32_t ;
struct psb_gtt {int mmu_gatt_start; int stolen_size; int gtt_pages; int gatt_start; } ;
struct drm_psb_private {int gatt_free_offset; int /*<<< orphan*/  lock_2d; int /*<<< orphan*/  irqmask_lock; struct psb_gtt gtt; } ;
struct drm_device {int /*<<< orphan*/  dev; struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PSB_CR_BIF_BANK0 ; 
 int /*<<< orphan*/  PSB_CR_BIF_BANK1 ; 
 int /*<<< orphan*/  PSB_CR_BIF_CTRL ; 
 int /*<<< orphan*/  PSB_CR_BIF_TWOD_REQ_BASE ; 
 int PSB_RSGX32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSB_WSGX32 (int,int /*<<< orphan*/ ) ; 
 int _PSB_MMU_ER_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  psb_spank (struct drm_psb_private*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int psb_do_init(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct psb_gtt *pg = &dev_priv->gtt;

	uint32_t stolen_gtt;

	if (pg->mmu_gatt_start & 0x0FFFFFFF) {
		dev_err(dev->dev, "Gatt must be 256M aligned. This is a bug.\n");
		return -EINVAL;
	}

	stolen_gtt = (pg->stolen_size >> PAGE_SHIFT) * 4;
	stolen_gtt = (stolen_gtt + PAGE_SIZE - 1) >> PAGE_SHIFT;
	stolen_gtt = (stolen_gtt < pg->gtt_pages) ? stolen_gtt : pg->gtt_pages;

	dev_priv->gatt_free_offset = pg->mmu_gatt_start +
	    (stolen_gtt << PAGE_SHIFT) * 1024;

	spin_lock_init(&dev_priv->irqmask_lock);
	spin_lock_init(&dev_priv->lock_2d);

	PSB_WSGX32(0x00000000, PSB_CR_BIF_BANK0);
	PSB_WSGX32(0x00000000, PSB_CR_BIF_BANK1);
	PSB_RSGX32(PSB_CR_BIF_BANK1);

	/* Do not bypass any MMU access, let them pagefault instead */
	PSB_WSGX32((PSB_RSGX32(PSB_CR_BIF_CTRL) & ~_PSB_MMU_ER_MASK),
		   PSB_CR_BIF_CTRL);
	PSB_RSGX32(PSB_CR_BIF_CTRL);

	psb_spank(dev_priv);

	/* mmu_gatt ?? */
	PSB_WSGX32(pg->gatt_start, PSB_CR_BIF_TWOD_REQ_BASE);
	PSB_RSGX32(PSB_CR_BIF_TWOD_REQ_BASE); /* Post */

	return 0;
}