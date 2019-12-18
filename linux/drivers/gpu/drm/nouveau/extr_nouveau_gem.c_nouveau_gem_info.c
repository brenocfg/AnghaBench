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
struct TYPE_8__ {scalar_t__ oclass; } ;
struct TYPE_9__ {TYPE_1__ object; } ;
struct nouveau_vmm {TYPE_2__ vmm; int /*<<< orphan*/  cli; } ;
struct nouveau_vma {int /*<<< orphan*/  addr; } ;
struct TYPE_13__ {scalar_t__ family; } ;
struct TYPE_14__ {TYPE_6__ info; } ;
struct nouveau_cli {TYPE_7__ device; struct nouveau_vmm vmm; struct nouveau_vmm svm; } ;
struct TYPE_11__ {int /*<<< orphan*/  vma_node; } ;
struct TYPE_10__ {scalar_t__ mem_type; int num_pages; } ;
struct TYPE_12__ {TYPE_4__ base; TYPE_3__ mem; int /*<<< orphan*/  offset; } ;
struct nouveau_bo {int kind; int comp; int zeta; scalar_t__ contig; int /*<<< orphan*/  mode; TYPE_5__ bo; int /*<<< orphan*/  valid_domains; } ;
struct drm_nouveau_gem_info {int size; int tile_flags; int /*<<< orphan*/  tile_mode; int /*<<< orphan*/  map_handle; int /*<<< orphan*/  offset; int /*<<< orphan*/  domain; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NOUVEAU_GEM_DOMAIN_GART ; 
 int /*<<< orphan*/  NOUVEAU_GEM_DOMAIN_VRAM ; 
 int NOUVEAU_GEM_TILE_NONCONTIG ; 
 scalar_t__ NVIF_CLASS_VMM_NV50 ; 
 scalar_t__ NV_DEVICE_INFO_V0_FERMI ; 
 scalar_t__ NV_DEVICE_INFO_V0_TESLA ; 
 int PAGE_SHIFT ; 
 scalar_t__ TTM_PL_TT ; 
 int /*<<< orphan*/  drm_vma_node_offset_addr (int /*<<< orphan*/ *) ; 
 scalar_t__ is_power_of_2 (int /*<<< orphan*/ ) ; 
 struct nouveau_cli* nouveau_cli (struct drm_file*) ; 
 struct nouveau_bo* nouveau_gem_object (struct drm_gem_object*) ; 
 struct nouveau_vma* nouveau_vma_find (struct nouveau_bo*,struct nouveau_vmm*) ; 

__attribute__((used)) static int
nouveau_gem_info(struct drm_file *file_priv, struct drm_gem_object *gem,
		 struct drm_nouveau_gem_info *rep)
{
	struct nouveau_cli *cli = nouveau_cli(file_priv);
	struct nouveau_bo *nvbo = nouveau_gem_object(gem);
	struct nouveau_vmm *vmm = cli->svm.cli ? &cli->svm : &cli->vmm;
	struct nouveau_vma *vma;

	if (is_power_of_2(nvbo->valid_domains))
		rep->domain = nvbo->valid_domains;
	else if (nvbo->bo.mem.mem_type == TTM_PL_TT)
		rep->domain = NOUVEAU_GEM_DOMAIN_GART;
	else
		rep->domain = NOUVEAU_GEM_DOMAIN_VRAM;
	rep->offset = nvbo->bo.offset;
	if (vmm->vmm.object.oclass >= NVIF_CLASS_VMM_NV50) {
		vma = nouveau_vma_find(nvbo, vmm);
		if (!vma)
			return -EINVAL;

		rep->offset = vma->addr;
	}

	rep->size = nvbo->bo.mem.num_pages << PAGE_SHIFT;
	rep->map_handle = drm_vma_node_offset_addr(&nvbo->bo.base.vma_node);
	rep->tile_mode = nvbo->mode;
	rep->tile_flags = nvbo->contig ? 0 : NOUVEAU_GEM_TILE_NONCONTIG;
	if (cli->device.info.family >= NV_DEVICE_INFO_V0_FERMI)
		rep->tile_flags |= nvbo->kind << 8;
	else
	if (cli->device.info.family >= NV_DEVICE_INFO_V0_TESLA)
		rep->tile_flags |= nvbo->kind << 8 | nvbo->comp << 16;
	else
		rep->tile_flags |= nvbo->zeta;
	return 0;
}