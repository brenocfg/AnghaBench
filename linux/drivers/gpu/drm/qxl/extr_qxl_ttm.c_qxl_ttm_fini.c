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
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;
struct qxl_device {TYPE_1__ mman; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int /*<<< orphan*/  TTM_PL_PRIV ; 
 int /*<<< orphan*/  TTM_PL_VRAM ; 
 int /*<<< orphan*/  ttm_bo_clean_mm (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_device_release (int /*<<< orphan*/ *) ; 

void qxl_ttm_fini(struct qxl_device *qdev)
{
	ttm_bo_clean_mm(&qdev->mman.bdev, TTM_PL_VRAM);
	ttm_bo_clean_mm(&qdev->mman.bdev, TTM_PL_PRIV);
	ttm_bo_device_release(&qdev->mman.bdev);
	DRM_INFO("qxl: ttm finalized\n");
}