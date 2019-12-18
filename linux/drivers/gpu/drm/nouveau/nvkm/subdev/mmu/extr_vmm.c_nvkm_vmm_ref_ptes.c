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
struct nvkm_vmm_pt {int /*<<< orphan*/ * refs; } ;
struct nvkm_vmm_iter {struct nvkm_vmm_pt** pt; struct nvkm_vmm_desc* desc; } ;
struct nvkm_vmm_desc {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPT ; 
 int /*<<< orphan*/  nvkm_vmm_ref_sptes (struct nvkm_vmm_iter*,struct nvkm_vmm_pt*,struct nvkm_vmm_desc const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
nvkm_vmm_ref_ptes(struct nvkm_vmm_iter *it, bool pfn, u32 ptei, u32 ptes)
{
	const struct nvkm_vmm_desc *desc = it->desc;
	const int type = desc->type == SPT;
	struct nvkm_vmm_pt *pgt = it->pt[0];

	/* Take PTE references. */
	pgt->refs[type] += ptes;

	/* Dual-PTs need special handling. */
	if (desc->type == SPT)
		nvkm_vmm_ref_sptes(it, pgt, desc, ptei, ptes);

	return true;
}