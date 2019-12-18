#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long u64 ;
typedef  int u32 ;
struct nvif_vmm {int page_nr; TYPE_8__* page; } ;
struct TYPE_15__ {scalar_t__ oclass; } ;
struct nvif_mmu {size_t* kind; TYPE_7__ object; } ;
struct TYPE_12__ {int /*<<< orphan*/  bdev; } ;
struct nouveau_drm {TYPE_4__ ttm; } ;
struct TYPE_13__ {scalar_t__ family; } ;
struct TYPE_14__ {TYPE_5__ info; } ;
struct TYPE_10__ {struct nvif_vmm vmm; } ;
struct TYPE_9__ {struct nvif_vmm vmm; scalar_t__ cli; } ;
struct nouveau_cli {TYPE_6__ device; TYPE_2__ vmm; TYPE_1__ svm; struct nvif_mmu mmu; struct nouveau_drm* drm; } ;
struct TYPE_11__ {int /*<<< orphan*/ * bdev; } ;
struct nouveau_bo {int force_coherent; int kind; int comp; int zeta; int mode; int contig; int page; TYPE_3__ bo; int /*<<< orphan*/  vma_list; int /*<<< orphan*/  entry; int /*<<< orphan*/  head; } ;
struct TYPE_16__ {int shift; scalar_t__ comp; int /*<<< orphan*/  host; int /*<<< orphan*/  vram; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct nouveau_bo* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NOUVEAU_GEM_TILE_NONCONTIG ; 
 scalar_t__ NVIF_CLASS_MMU_GF100 ; 
 scalar_t__ NV_DEVICE_INFO_V0_CURIE ; 
 scalar_t__ NV_DEVICE_INFO_V0_FERMI ; 
 scalar_t__ NV_DEVICE_INFO_V0_TESLA ; 
 int /*<<< orphan*/  NV_WARN (struct nouveau_drm*,char*,unsigned long long) ; 
 int PAGE_SHIFT ; 
 int TTM_PL_FLAG_TT ; 
 int TTM_PL_FLAG_UNCACHED ; 
 int TTM_PL_FLAG_VRAM ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct nouveau_bo*) ; 
 struct nouveau_bo* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_bo_fixup_align (struct nouveau_bo*,int,int*,unsigned long long*) ; 
 int /*<<< orphan*/  nouveau_drm_use_coherent_gpu_mapping (struct nouveau_drm*) ; 
 int /*<<< orphan*/  nvif_mmu_kind_valid (struct nvif_mmu*,int) ; 

struct nouveau_bo *
nouveau_bo_alloc(struct nouveau_cli *cli, u64 *size, int *align, u32 flags,
		 u32 tile_mode, u32 tile_flags)
{
	struct nouveau_drm *drm = cli->drm;
	struct nouveau_bo *nvbo;
	struct nvif_mmu *mmu = &cli->mmu;
	struct nvif_vmm *vmm = cli->svm.cli ? &cli->svm.vmm : &cli->vmm.vmm;
	int i, pi = -1;

	if (!*size) {
		NV_WARN(drm, "skipped size %016llx\n", *size);
		return ERR_PTR(-EINVAL);
	}

	nvbo = kzalloc(sizeof(struct nouveau_bo), GFP_KERNEL);
	if (!nvbo)
		return ERR_PTR(-ENOMEM);
	INIT_LIST_HEAD(&nvbo->head);
	INIT_LIST_HEAD(&nvbo->entry);
	INIT_LIST_HEAD(&nvbo->vma_list);
	nvbo->bo.bdev = &drm->ttm.bdev;

	/* This is confusing, and doesn't actually mean we want an uncached
	 * mapping, but is what NOUVEAU_GEM_DOMAIN_COHERENT gets translated
	 * into in nouveau_gem_new().
	 */
	if (flags & TTM_PL_FLAG_UNCACHED) {
		/* Determine if we can get a cache-coherent map, forcing
		 * uncached mapping if we can't.
		 */
		if (!nouveau_drm_use_coherent_gpu_mapping(drm))
			nvbo->force_coherent = true;
	}

	if (cli->device.info.family >= NV_DEVICE_INFO_V0_FERMI) {
		nvbo->kind = (tile_flags & 0x0000ff00) >> 8;
		if (!nvif_mmu_kind_valid(mmu, nvbo->kind)) {
			kfree(nvbo);
			return ERR_PTR(-EINVAL);
		}

		nvbo->comp = mmu->kind[nvbo->kind] != nvbo->kind;
	} else
	if (cli->device.info.family >= NV_DEVICE_INFO_V0_TESLA) {
		nvbo->kind = (tile_flags & 0x00007f00) >> 8;
		nvbo->comp = (tile_flags & 0x00030000) >> 16;
		if (!nvif_mmu_kind_valid(mmu, nvbo->kind)) {
			kfree(nvbo);
			return ERR_PTR(-EINVAL);
		}
	} else {
		nvbo->zeta = (tile_flags & 0x00000007);
	}
	nvbo->mode = tile_mode;
	nvbo->contig = !(tile_flags & NOUVEAU_GEM_TILE_NONCONTIG);

	/* Determine the desirable target GPU page size for the buffer. */
	for (i = 0; i < vmm->page_nr; i++) {
		/* Because we cannot currently allow VMM maps to fail
		 * during buffer migration, we need to determine page
		 * size for the buffer up-front, and pre-allocate its
		 * page tables.
		 *
		 * Skip page sizes that can't support needed domains.
		 */
		if (cli->device.info.family > NV_DEVICE_INFO_V0_CURIE &&
		    (flags & TTM_PL_FLAG_VRAM) && !vmm->page[i].vram)
			continue;
		if ((flags & TTM_PL_FLAG_TT) &&
		    (!vmm->page[i].host || vmm->page[i].shift > PAGE_SHIFT))
			continue;

		/* Select this page size if it's the first that supports
		 * the potential memory domains, or when it's compatible
		 * with the requested compression settings.
		 */
		if (pi < 0 || !nvbo->comp || vmm->page[i].comp)
			pi = i;

		/* Stop once the buffer is larger than the current page size. */
		if (*size >= 1ULL << vmm->page[i].shift)
			break;
	}

	if (WARN_ON(pi < 0))
		return ERR_PTR(-EINVAL);

	/* Disable compression if suitable settings couldn't be found. */
	if (nvbo->comp && !vmm->page[pi].comp) {
		if (mmu->object.oclass >= NVIF_CLASS_MMU_GF100)
			nvbo->kind = mmu->kind[nvbo->kind];
		nvbo->comp = 0;
	}
	nvbo->page = vmm->page[pi].shift;

	nouveau_bo_fixup_align(nvbo, flags, align, size);

	return nvbo;
}