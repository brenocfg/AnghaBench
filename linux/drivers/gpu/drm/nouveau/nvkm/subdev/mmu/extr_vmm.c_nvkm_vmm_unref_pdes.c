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
typedef  size_t u32 ;
struct nvkm_vmm_pt {scalar_t__* refs; int /*<<< orphan*/ ** pde; struct nvkm_mmu_pt** pt; scalar_t__ sparse; } ;
struct nvkm_vmm_iter {size_t lvl; size_t* pte; struct nvkm_vmm* vmm; struct nvkm_vmm_pt** pt; struct nvkm_vmm_desc* desc; } ;
struct nvkm_vmm_desc_func {int /*<<< orphan*/  (* pde ) (struct nvkm_vmm*,struct nvkm_vmm_pt*,size_t) ;int /*<<< orphan*/  (* unmap ) (struct nvkm_vmm*,struct nvkm_mmu_pt*,size_t,int) ;int /*<<< orphan*/  (* sparse ) (struct nvkm_vmm*,struct nvkm_mmu_pt*,size_t,int) ;} ;
struct nvkm_vmm_desc {struct nvkm_vmm_desc_func* func; int /*<<< orphan*/  type; } ;
struct nvkm_vmm {int /*<<< orphan*/  bootstrapped; int /*<<< orphan*/  mmu; } ;
struct nvkm_mmu_pt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * NVKM_VMM_PDE_SPARSE ; 
 int /*<<< orphan*/  SPT ; 
 int /*<<< orphan*/  TRA (struct nvkm_vmm_iter*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_mmu_ptc_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nvkm_mmu_pt**) ; 
 int /*<<< orphan*/  nvkm_vmm_desc_type (struct nvkm_vmm_desc const*) ; 
 int /*<<< orphan*/  nvkm_vmm_flush (struct nvkm_vmm_iter*) ; 
 int /*<<< orphan*/  nvkm_vmm_flush_mark (struct nvkm_vmm_iter*) ; 
 int /*<<< orphan*/  nvkm_vmm_pt_del (struct nvkm_vmm_pt**) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_vmm*,struct nvkm_mmu_pt*,size_t,int) ; 
 int /*<<< orphan*/  stub2 (struct nvkm_vmm*,struct nvkm_mmu_pt*,size_t,int) ; 
 int /*<<< orphan*/  stub3 (struct nvkm_vmm*,struct nvkm_vmm_pt*,size_t) ; 
 int /*<<< orphan*/  stub4 (struct nvkm_vmm*,struct nvkm_vmm_pt*,size_t) ; 

__attribute__((used)) static void
nvkm_vmm_unref_pdes(struct nvkm_vmm_iter *it)
{
	const struct nvkm_vmm_desc *desc = it->desc;
	const int type = desc[it->lvl].type == SPT;
	struct nvkm_vmm_pt *pgd = it->pt[it->lvl + 1];
	struct nvkm_vmm_pt *pgt = it->pt[it->lvl];
	struct nvkm_mmu_pt *pt = pgt->pt[type];
	struct nvkm_vmm *vmm = it->vmm;
	u32 pdei = it->pte[it->lvl + 1];

	/* Recurse up the tree, unreferencing/destroying unneeded PDs. */
	it->lvl++;
	if (--pgd->refs[0]) {
		const struct nvkm_vmm_desc_func *func = desc[it->lvl].func;
		/* PD has other valid PDEs, so we need a proper update. */
		TRA(it, "PDE unmap %s", nvkm_vmm_desc_type(&desc[it->lvl - 1]));
		pgt->pt[type] = NULL;
		if (!pgt->refs[!type]) {
			/* PDE no longer required. */
			if (pgd->pt[0]) {
				if (pgt->sparse) {
					func->sparse(vmm, pgd->pt[0], pdei, 1);
					pgd->pde[pdei] = NVKM_VMM_PDE_SPARSE;
				} else {
					func->unmap(vmm, pgd->pt[0], pdei, 1);
					pgd->pde[pdei] = NULL;
				}
			} else {
				/* Special handling for Tesla-class GPUs,
				 * where there's no central PD, but each
				 * instance has its own embedded PD.
				 */
				func->pde(vmm, pgd, pdei);
				pgd->pde[pdei] = NULL;
			}
		} else {
			/* PDE was pointing at dual-PTs and we're removing
			 * one of them, leaving the other in place.
			 */
			func->pde(vmm, pgd, pdei);
		}

		/* GPU may have cached the PTs, flush before freeing. */
		nvkm_vmm_flush_mark(it);
		nvkm_vmm_flush(it);
	} else {
		/* PD has no valid PDEs left, so we can just destroy it. */
		nvkm_vmm_unref_pdes(it);
	}

	/* Destroy PD/PT. */
	TRA(it, "PDE free %s", nvkm_vmm_desc_type(&desc[it->lvl - 1]));
	nvkm_mmu_ptc_put(vmm->mmu, vmm->bootstrapped, &pt);
	if (!pgt->refs[!type])
		nvkm_vmm_pt_del(&pgt);
	it->lvl--;
}