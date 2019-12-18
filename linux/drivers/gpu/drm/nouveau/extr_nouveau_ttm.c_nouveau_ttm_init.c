#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_14__ {int size; int /*<<< orphan*/  cma; int /*<<< orphan*/  base; scalar_t__ bridge; } ;
struct nvkm_pci {TYPE_1__ agp; } ;
struct nvkm_device {TYPE_4__* func; struct nvkm_pci* pci; } ;
struct nvif_mmu {int dmabits; } ;
struct TYPE_12__ {int vram_available; int gart_available; } ;
struct TYPE_22__ {int type_vram; int /*<<< orphan*/  bdev; int /*<<< orphan*/  mtrr; } ;
struct TYPE_21__ {int size; scalar_t__ bridge; int /*<<< orphan*/  cma; int /*<<< orphan*/  base; } ;
struct TYPE_18__ {int limit; } ;
struct TYPE_19__ {TYPE_5__ vmm; } ;
struct TYPE_16__ {scalar_t__ family; int chipset; scalar_t__ platform; int ram_user; } ;
struct TYPE_13__ {TYPE_3__ info; } ;
struct TYPE_20__ {TYPE_6__ vmm; TYPE_11__ device; struct nvif_mmu mmu; } ;
struct nouveau_drm {TYPE_10__ gem; TYPE_9__ ttm; TYPE_8__ agp; TYPE_7__ client; struct drm_device* dev; } ;
struct drm_device {TYPE_2__* anon_inode; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* resource_size ) (struct nvkm_device*,int) ;int /*<<< orphan*/  (* resource_addr ) (struct nvkm_device*,int) ;} ;
struct TYPE_15__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int ENOSYS ; 
 int NVIF_MEM_COMP ; 
 int NVIF_MEM_DISP ; 
 int NVIF_MEM_KIND ; 
 int NVIF_MEM_MAPPABLE ; 
 int NVIF_MEM_VRAM ; 
 scalar_t__ NV_DEVICE_INFO_V0_SOC ; 
 scalar_t__ NV_DEVICE_INFO_V0_TESLA ; 
 int /*<<< orphan*/  NV_ERROR (struct nouveau_drm*,char*,int) ; 
 int /*<<< orphan*/  NV_INFO (struct nouveau_drm*,char*,int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  TTM_PL_TT ; 
 int /*<<< orphan*/  TTM_PL_VRAM ; 
 int /*<<< orphan*/  arch_io_reserve_memtype_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_phys_wc_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_bo_driver ; 
 int nouveau_ttm_init_host (struct nouveau_drm*,int) ; 
 int nvif_mmu_type (struct nvif_mmu*,int) ; 
 struct nvkm_device* nvxx_device (TYPE_11__*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  stub2 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  stub3 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  stub4 (struct nvkm_device*,int) ; 
 int ttm_bo_device_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ttm_bo_init_mm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
nouveau_ttm_init(struct nouveau_drm *drm)
{
	struct nvkm_device *device = nvxx_device(&drm->client.device);
	struct nvkm_pci *pci = device->pci;
	struct nvif_mmu *mmu = &drm->client.mmu;
	struct drm_device *dev = drm->dev;
	int typei, ret;

	ret = nouveau_ttm_init_host(drm, 0);
	if (ret)
		return ret;

	if (drm->client.device.info.family >= NV_DEVICE_INFO_V0_TESLA &&
	    drm->client.device.info.chipset != 0x50) {
		ret = nouveau_ttm_init_host(drm, NVIF_MEM_KIND);
		if (ret)
			return ret;
	}

	if (drm->client.device.info.platform != NV_DEVICE_INFO_V0_SOC &&
	    drm->client.device.info.family >= NV_DEVICE_INFO_V0_TESLA) {
		typei = nvif_mmu_type(mmu, NVIF_MEM_VRAM | NVIF_MEM_MAPPABLE |
					   NVIF_MEM_KIND |
					   NVIF_MEM_COMP |
					   NVIF_MEM_DISP);
		if (typei < 0)
			return -ENOSYS;

		drm->ttm.type_vram = typei;
	} else {
		drm->ttm.type_vram = -1;
	}

	if (pci && pci->agp.bridge) {
		drm->agp.bridge = pci->agp.bridge;
		drm->agp.base = pci->agp.base;
		drm->agp.size = pci->agp.size;
		drm->agp.cma = pci->agp.cma;
	}

	ret = ttm_bo_device_init(&drm->ttm.bdev,
				  &nouveau_bo_driver,
				  dev->anon_inode->i_mapping,
				  drm->client.mmu.dmabits <= 32 ? true : false);
	if (ret) {
		NV_ERROR(drm, "error initialising bo driver, %d\n", ret);
		return ret;
	}

	/* VRAM init */
	drm->gem.vram_available = drm->client.device.info.ram_user;

	arch_io_reserve_memtype_wc(device->func->resource_addr(device, 1),
				   device->func->resource_size(device, 1));

	ret = ttm_bo_init_mm(&drm->ttm.bdev, TTM_PL_VRAM,
			      drm->gem.vram_available >> PAGE_SHIFT);
	if (ret) {
		NV_ERROR(drm, "VRAM mm init failed, %d\n", ret);
		return ret;
	}

	drm->ttm.mtrr = arch_phys_wc_add(device->func->resource_addr(device, 1),
					 device->func->resource_size(device, 1));

	/* GART init */
	if (!drm->agp.bridge) {
		drm->gem.gart_available = drm->client.vmm.vmm.limit;
	} else {
		drm->gem.gart_available = drm->agp.size;
	}

	ret = ttm_bo_init_mm(&drm->ttm.bdev, TTM_PL_TT,
			      drm->gem.gart_available >> PAGE_SHIFT);
	if (ret) {
		NV_ERROR(drm, "GART mm init failed, %d\n", ret);
		return ret;
	}

	NV_INFO(drm, "VRAM: %d MiB\n", (u32)(drm->gem.vram_available >> 20));
	NV_INFO(drm, "GART: %d MiB\n", (u32)(drm->gem.gart_available >> 20));
	return 0;
}