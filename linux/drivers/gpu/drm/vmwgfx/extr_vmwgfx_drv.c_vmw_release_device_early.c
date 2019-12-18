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
struct vmw_private {int /*<<< orphan*/  bdev; scalar_t__ has_mob; scalar_t__ cman; int /*<<< orphan*/  dummy_query_bo; int /*<<< orphan*/ * pinned_bo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMW_PL_MOB ; 
 int /*<<< orphan*/  ttm_bo_evict_mm (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_bo_unreference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_cmdbuf_remove_pool (scalar_t__) ; 
 int /*<<< orphan*/  vmw_otables_takedown (struct vmw_private*) ; 

__attribute__((used)) static void vmw_release_device_early(struct vmw_private *dev_priv)
{
	/*
	 * Previous destructions should've released
	 * the pinned bo.
	 */

	BUG_ON(dev_priv->pinned_bo != NULL);

	vmw_bo_unreference(&dev_priv->dummy_query_bo);
	if (dev_priv->cman)
		vmw_cmdbuf_remove_pool(dev_priv->cman);

	if (dev_priv->has_mob) {
		ttm_bo_evict_mm(&dev_priv->bdev, VMW_PL_MOB);
		vmw_otables_takedown(dev_priv);
	}
}