#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct nvkm_vmm_page {int shift; int type; } ;
struct nvkm_vmm_map {int type; int ctag; int next; int offset; TYPE_7__* tags; TYPE_4__* mem; struct nvkm_memory* memory; struct nvkm_vmm_page* page; } ;
struct nvkm_vmm {TYPE_6__* mmu; } ;
struct nvkm_ram {int stolen; } ;
struct nvkm_memory {int dummy; } ;
struct nvkm_device {TYPE_2__* fb; } ;
struct nv50_vmm_map_vn {int dummy; } ;
struct nv50_vmm_map_v0 {int kind; int comp; int /*<<< orphan*/  priv; int /*<<< orphan*/  ro; } ;
struct TYPE_14__ {TYPE_5__* mn; } ;
struct TYPE_8__ {struct nvkm_device* device; } ;
struct TYPE_13__ {TYPE_3__* func; TYPE_1__ subdev; } ;
struct TYPE_12__ {int offset; } ;
struct TYPE_11__ {int const type; } ;
struct TYPE_10__ {int* (* kind ) (TYPE_6__*,int*) ;} ;
struct TYPE_9__ {struct nvkm_ram* ram; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOSYS ; 
#define  NVKM_MEM_TARGET_HOST 130 
#define  NVKM_MEM_TARGET_NCOH 129 
#define  NVKM_MEM_TARGET_VRAM 128 
 int NVKM_VMM_PAGE_COMP ; 
 int /*<<< orphan*/  VMM_DEBUG (struct nvkm_vmm*,char*,...) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int nvif_unpack (int,void**,int*,struct nv50_vmm_map_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nvif_unvers (int,void**,int*,struct nv50_vmm_map_vn) ; 
 int nvkm_memory_size (struct nvkm_memory*) ; 
 int nvkm_memory_tags_get (struct nvkm_memory*,struct nvkm_device*,int,int /*<<< orphan*/ *,TYPE_7__**) ; 
 int nvkm_memory_target (struct nvkm_memory*) ; 
 int* stub1 (TYPE_6__*,int*) ; 

int
nv50_vmm_valid(struct nvkm_vmm *vmm, void *argv, u32 argc,
	       struct nvkm_vmm_map *map)
{
	const struct nvkm_vmm_page *page = map->page;
	union {
		struct nv50_vmm_map_vn vn;
		struct nv50_vmm_map_v0 v0;
	} *args = argv;
	struct nvkm_device *device = vmm->mmu->subdev.device;
	struct nvkm_ram *ram = device->fb->ram;
	struct nvkm_memory *memory = map->memory;
	u8  aper, kind, comp, priv, ro;
	int kindn, ret = -ENOSYS;
	const u8 *kindm;

	map->type = map->ctag = 0;
	map->next = 1 << page->shift;

	if (!(ret = nvif_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) {
		ro   = !!args->v0.ro;
		priv = !!args->v0.priv;
		kind = args->v0.kind & 0x7f;
		comp = args->v0.comp & 0x03;
	} else
	if (!(ret = nvif_unvers(ret, &argv, &argc, args->vn))) {
		ro   = 0;
		priv = 0;
		kind = 0x00;
		comp = 0;
	} else {
		VMM_DEBUG(vmm, "args");
		return ret;
	}

	switch (nvkm_memory_target(memory)) {
	case NVKM_MEM_TARGET_VRAM:
		if (ram->stolen) {
			map->type |= ram->stolen;
			aper = 3;
		} else {
			aper = 0;
		}
		break;
	case NVKM_MEM_TARGET_HOST:
		aper = 2;
		break;
	case NVKM_MEM_TARGET_NCOH:
		aper = 3;
		break;
	default:
		WARN_ON(1);
		return -EINVAL;
	}

	kindm = vmm->mmu->func->kind(vmm->mmu, &kindn);
	if (kind >= kindn || kindm[kind] == 0x7f) {
		VMM_DEBUG(vmm, "kind %02x", kind);
		return -EINVAL;
	}

	if (map->mem && map->mem->type != kindm[kind]) {
		VMM_DEBUG(vmm, "kind %02x bankswz: %d %d", kind,
			  kindm[kind], map->mem->type);
		return -EINVAL;
	}

	if (comp) {
		u32 tags = (nvkm_memory_size(memory) >> 16) * comp;
		if (aper != 0 || !(page->type & NVKM_VMM_PAGE_COMP)) {
			VMM_DEBUG(vmm, "comp %d %02x", aper, page->type);
			return -EINVAL;
		}

		ret = nvkm_memory_tags_get(memory, device, tags, NULL,
					   &map->tags);
		if (ret) {
			VMM_DEBUG(vmm, "comp %d", ret);
			return ret;
		}

		if (map->tags->mn) {
			u32 tags = map->tags->mn->offset + (map->offset >> 16);
			map->ctag |= (u64)comp << 49;
			map->type |= (u64)comp << 47;
			map->type |= (u64)tags << 49;
			map->next |= map->ctag;
		}
	}

	map->type |= BIT(0); /* Valid. */
	map->type |= (u64)ro << 3;
	map->type |= (u64)aper << 4;
	map->type |= (u64)priv << 6;
	map->type |= (u64)kind << 40;
	return 0;
}