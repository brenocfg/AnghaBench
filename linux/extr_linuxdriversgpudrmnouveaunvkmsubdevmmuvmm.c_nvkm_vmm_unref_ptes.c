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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_vmm_pt {scalar_t__* refs; } ;
struct nvkm_vmm_iter {int /*<<< orphan*/  lvl; struct nvkm_vmm_pt** pt; struct nvkm_vmm_desc* desc; } ;
struct nvkm_vmm_desc {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPT ; 
 int /*<<< orphan*/  TRA (struct nvkm_vmm_iter*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_vmm_desc_type (struct nvkm_vmm_desc const*) ; 
 int /*<<< orphan*/  nvkm_vmm_unref_pdes (struct nvkm_vmm_iter*) ; 
 int /*<<< orphan*/  nvkm_vmm_unref_sptes (struct nvkm_vmm_iter*,struct nvkm_vmm_pt*,struct nvkm_vmm_desc const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
nvkm_vmm_unref_ptes(struct nvkm_vmm_iter *it, u32 ptei, u32 ptes)
{
	const struct nvkm_vmm_desc *desc = it->desc;
	const int type = desc->type == SPT;
	struct nvkm_vmm_pt *pgt = it->pt[0];

	/* Drop PTE references. */
	pgt->refs[type] -= ptes;

	/* Dual-PTs need special handling, unless PDE becoming invalid. */
	if (desc->type == SPT && (pgt->refs[0] || pgt->refs[1]))
		nvkm_vmm_unref_sptes(it, pgt, desc, ptei, ptes);

	/* PT no longer neeed?  Destroy it. */
	if (!pgt->refs[type]) {
		it->lvl++;
		TRA(it, "%s empty", nvkm_vmm_desc_type(desc));
		it->lvl--;
		nvkm_vmm_unref_pdes(it);
		return false; /* PTE writes for unmap() not necessary. */
	}

	return true;
}