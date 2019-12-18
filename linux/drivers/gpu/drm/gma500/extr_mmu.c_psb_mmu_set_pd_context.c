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
typedef  scalar_t__ uint32_t ;
struct psb_mmu_pd {int hw_context; TYPE_1__* driver; int /*<<< orphan*/  p; } ;
struct drm_psb_private {int dummy; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  sem; struct drm_device* dev; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 scalar_t__ PSB_CR_BIF_DIR_LIST_BASE0 ; 
 scalar_t__ PSB_CR_BIF_DIR_LIST_BASE1 ; 
 int /*<<< orphan*/  PSB_WSGX32 (int,scalar_t__) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int page_to_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psb_mmu_flush_pd_locked (TYPE_1__*,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

void psb_mmu_set_pd_context(struct psb_mmu_pd *pd, int hw_context)
{
	struct drm_device *dev = pd->driver->dev;
	struct drm_psb_private *dev_priv = dev->dev_private;
	uint32_t offset = (hw_context == 0) ? PSB_CR_BIF_DIR_LIST_BASE0 :
			  PSB_CR_BIF_DIR_LIST_BASE1 + hw_context * 4;

	down_write(&pd->driver->sem);
	PSB_WSGX32(page_to_pfn(pd->p) << PAGE_SHIFT, offset);
	wmb();
	psb_mmu_flush_pd_locked(pd->driver, 1);
	pd->hw_context = hw_context;
	up_write(&pd->driver->sem);

}