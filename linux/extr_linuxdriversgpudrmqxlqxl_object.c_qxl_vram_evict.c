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
 int /*<<< orphan*/  TTM_PL_VRAM ; 
 int ttm_bo_evict_mm (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int qxl_vram_evict(struct qxl_device *qdev)
{
	return ttm_bo_evict_mm(&qdev->mman.bdev, TTM_PL_VRAM);
}