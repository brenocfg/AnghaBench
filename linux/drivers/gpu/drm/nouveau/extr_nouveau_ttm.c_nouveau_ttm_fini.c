#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nvkm_device {TYPE_1__* func; } ;
struct TYPE_6__ {scalar_t__ mtrr; int /*<<< orphan*/  bdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  device; } ;
struct nouveau_drm {TYPE_3__ ttm; TYPE_2__ client; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* resource_size ) (struct nvkm_device*,int) ;int /*<<< orphan*/  (* resource_addr ) (struct nvkm_device*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TTM_PL_TT ; 
 int /*<<< orphan*/  TTM_PL_VRAM ; 
 int /*<<< orphan*/  arch_io_free_memtype_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_phys_wc_del (scalar_t__) ; 
 struct nvkm_device* nvxx_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  stub2 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  ttm_bo_clean_mm (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_device_release (int /*<<< orphan*/ *) ; 

void
nouveau_ttm_fini(struct nouveau_drm *drm)
{
	struct nvkm_device *device = nvxx_device(&drm->client.device);

	ttm_bo_clean_mm(&drm->ttm.bdev, TTM_PL_VRAM);
	ttm_bo_clean_mm(&drm->ttm.bdev, TTM_PL_TT);

	ttm_bo_device_release(&drm->ttm.bdev);

	arch_phys_wc_del(drm->ttm.mtrr);
	drm->ttm.mtrr = 0;
	arch_io_free_memtype_wc(device->func->resource_addr(device, 1),
				device->func->resource_size(device, 1));

}