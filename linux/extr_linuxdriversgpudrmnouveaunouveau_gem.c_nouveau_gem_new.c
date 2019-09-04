#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {scalar_t__ family; } ;
struct TYPE_8__ {TYPE_1__ info; } ;
struct TYPE_9__ {TYPE_2__ device; } ;
struct nouveau_drm {int /*<<< orphan*/  dev; TYPE_3__ client; } ;
struct nouveau_cli {struct nouveau_drm* drm; } ;
struct TYPE_12__ {int /*<<< orphan*/  filp; } ;
struct TYPE_10__ {int /*<<< orphan*/  size; } ;
struct TYPE_11__ {int /*<<< orphan*/  persistent_swap_storage; TYPE_4__ mem; } ;
struct nouveau_bo {int valid_domains; TYPE_6__ gem; TYPE_5__ bo; } ;

/* Variables and functions */
 int ENOMEM ; 
 int NOUVEAU_GEM_DOMAIN_COHERENT ; 
 int NOUVEAU_GEM_DOMAIN_CPU ; 
 int NOUVEAU_GEM_DOMAIN_GART ; 
 int NOUVEAU_GEM_DOMAIN_VRAM ; 
 scalar_t__ NV_DEVICE_INFO_V0_TESLA ; 
 int /*<<< orphan*/  TTM_PL_FLAG_SYSTEM ; 
 int /*<<< orphan*/  TTM_PL_FLAG_TT ; 
 int /*<<< orphan*/  TTM_PL_FLAG_UNCACHED ; 
 int /*<<< orphan*/  TTM_PL_FLAG_VRAM ; 
 int drm_gem_object_init (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int nouveau_bo_new (struct nouveau_cli*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nouveau_bo**) ; 
 int /*<<< orphan*/  nouveau_bo_ref (int /*<<< orphan*/ *,struct nouveau_bo**) ; 

int
nouveau_gem_new(struct nouveau_cli *cli, u64 size, int align, uint32_t domain,
		uint32_t tile_mode, uint32_t tile_flags,
		struct nouveau_bo **pnvbo)
{
	struct nouveau_drm *drm = cli->drm;
	struct nouveau_bo *nvbo;
	u32 flags = 0;
	int ret;

	if (domain & NOUVEAU_GEM_DOMAIN_VRAM)
		flags |= TTM_PL_FLAG_VRAM;
	if (domain & NOUVEAU_GEM_DOMAIN_GART)
		flags |= TTM_PL_FLAG_TT;
	if (!flags || domain & NOUVEAU_GEM_DOMAIN_CPU)
		flags |= TTM_PL_FLAG_SYSTEM;

	if (domain & NOUVEAU_GEM_DOMAIN_COHERENT)
		flags |= TTM_PL_FLAG_UNCACHED;

	ret = nouveau_bo_new(cli, size, align, flags, tile_mode,
			     tile_flags, NULL, NULL, pnvbo);
	if (ret)
		return ret;
	nvbo = *pnvbo;

	/* we restrict allowed domains on nv50+ to only the types
	 * that were requested at creation time.  not possibly on
	 * earlier chips without busting the ABI.
	 */
	nvbo->valid_domains = NOUVEAU_GEM_DOMAIN_VRAM |
			      NOUVEAU_GEM_DOMAIN_GART;
	if (drm->client.device.info.family >= NV_DEVICE_INFO_V0_TESLA)
		nvbo->valid_domains &= domain;

	/* Initialize the embedded gem-object. We return a single gem-reference
	 * to the caller, instead of a normal nouveau_bo ttm reference. */
	ret = drm_gem_object_init(drm->dev, &nvbo->gem, nvbo->bo.mem.size);
	if (ret) {
		nouveau_bo_ref(NULL, pnvbo);
		return -ENOMEM;
	}

	nvbo->bo.persistent_swap_storage = nvbo->gem.filp;
	return 0;
}