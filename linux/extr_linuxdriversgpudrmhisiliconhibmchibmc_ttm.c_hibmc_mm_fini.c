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
struct hibmc_drm_private {int mm_inited; int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hibmc_ttm_global_release (struct hibmc_drm_private*) ; 
 int /*<<< orphan*/  ttm_bo_device_release (int /*<<< orphan*/ *) ; 

void hibmc_mm_fini(struct hibmc_drm_private *hibmc)
{
	if (!hibmc->mm_inited)
		return;

	ttm_bo_device_release(&hibmc->bdev);
	hibmc_ttm_global_release(hibmc);
	hibmc->mm_inited = false;
}