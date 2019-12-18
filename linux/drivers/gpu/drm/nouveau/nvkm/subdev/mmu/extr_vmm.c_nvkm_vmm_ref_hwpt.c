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
typedef  size_t u32 ;
struct nvkm_vmm_pt {int* pte; scalar_t__ sparse; scalar_t__* refs; struct nvkm_mmu_pt** pt; struct nvkm_vmm_pt** pde; } ;
struct nvkm_vmm_iter {int lvl; struct nvkm_vmm* vmm; struct nvkm_vmm_desc* desc; } ;
struct nvkm_vmm_desc {int bits; size_t size; TYPE_1__* func; int /*<<< orphan*/  type; int /*<<< orphan*/  align; } ;
struct nvkm_vmm {struct nvkm_mmu* mmu; } ;
struct nvkm_mmu_pt {int dummy; } ;
struct nvkm_mmu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* pde ) (struct nvkm_vmm*,struct nvkm_vmm_pt*,size_t) ;int /*<<< orphan*/  (* invalid ) (struct nvkm_vmm*,struct nvkm_mmu_pt*,size_t,size_t) ;int /*<<< orphan*/  (* sparse ) (struct nvkm_vmm*,struct nvkm_mmu_pt*,size_t,size_t) ;int /*<<< orphan*/  (* unmap ) (struct nvkm_vmm*,struct nvkm_mmu_pt*,size_t,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LPT ; 
 int NVKM_VMM_PTE_SPTES ; 
 int NVKM_VMM_PTE_VALID ; 
 int /*<<< orphan*/  SPT ; 
 int /*<<< orphan*/  TRA (struct nvkm_vmm_iter*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,size_t) ; 
 struct nvkm_mmu_pt* nvkm_mmu_ptc_get (struct nvkm_mmu*,size_t,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  nvkm_vmm_desc_type (struct nvkm_vmm_desc const*) ; 
 int /*<<< orphan*/  nvkm_vmm_flush_mark (struct nvkm_vmm_iter*) ; 
 int /*<<< orphan*/  nvkm_vmm_sparse_ptes (struct nvkm_vmm_desc const*,struct nvkm_vmm_pt*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  nvkm_vmm_unref_pdes (struct nvkm_vmm_iter*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_vmm*,struct nvkm_mmu_pt*,size_t,size_t) ; 
 int /*<<< orphan*/  stub2 (struct nvkm_vmm*,struct nvkm_mmu_pt*,size_t,size_t) ; 
 int /*<<< orphan*/  stub3 (struct nvkm_vmm*,struct nvkm_mmu_pt*,size_t,size_t) ; 
 int /*<<< orphan*/  stub4 (struct nvkm_vmm*,struct nvkm_mmu_pt*,size_t,size_t) ; 
 int /*<<< orphan*/  stub5 (struct nvkm_vmm*,struct nvkm_mmu_pt*,size_t,size_t) ; 
 int /*<<< orphan*/  stub6 (struct nvkm_vmm*,struct nvkm_vmm_pt*,size_t) ; 

__attribute__((used)) static bool
nvkm_vmm_ref_hwpt(struct nvkm_vmm_iter *it, struct nvkm_vmm_pt *pgd, u32 pdei)
{
	const struct nvkm_vmm_desc *desc = &it->desc[it->lvl - 1];
	const int type = desc->type == SPT;
	struct nvkm_vmm_pt *pgt = pgd->pde[pdei];
	const bool zero = !pgt->sparse && !desc->func->invalid;
	struct nvkm_vmm *vmm = it->vmm;
	struct nvkm_mmu *mmu = vmm->mmu;
	struct nvkm_mmu_pt *pt;
	u32 pten = 1 << desc->bits;
	u32 pteb, ptei, ptes;
	u32 size = desc->size * pten;

	pgd->refs[0]++;

	pgt->pt[type] = nvkm_mmu_ptc_get(mmu, size, desc->align, zero);
	if (!pgt->pt[type]) {
		it->lvl--;
		nvkm_vmm_unref_pdes(it);
		return false;
	}

	if (zero)
		goto done;

	pt = pgt->pt[type];

	if (desc->type == LPT && pgt->refs[1]) {
		/* SPT already exists covering the same range as this LPT,
		 * which means we need to be careful that any LPTEs which
		 * overlap valid SPTEs are unmapped as opposed to invalid
		 * or sparse, which would prevent the MMU from looking at
		 * the SPTEs on some GPUs.
		 */
		for (ptei = pteb = 0; ptei < pten; pteb = ptei) {
			bool spte = pgt->pte[ptei] & NVKM_VMM_PTE_SPTES;
			for (ptes = 1, ptei++; ptei < pten; ptes++, ptei++) {
				bool next = pgt->pte[ptei] & NVKM_VMM_PTE_SPTES;
				if (spte != next)
					break;
			}

			if (!spte) {
				if (pgt->sparse)
					desc->func->sparse(vmm, pt, pteb, ptes);
				else
					desc->func->invalid(vmm, pt, pteb, ptes);
				memset(&pgt->pte[pteb], 0x00, ptes);
			} else {
				desc->func->unmap(vmm, pt, pteb, ptes);
				while (ptes--)
					pgt->pte[pteb++] |= NVKM_VMM_PTE_VALID;
			}
		}
	} else {
		if (pgt->sparse) {
			nvkm_vmm_sparse_ptes(desc, pgt, 0, pten);
			desc->func->sparse(vmm, pt, 0, pten);
		} else {
			desc->func->invalid(vmm, pt, 0, pten);
		}
	}

done:
	TRA(it, "PDE write %s", nvkm_vmm_desc_type(desc));
	it->desc[it->lvl].func->pde(it->vmm, pgd, pdei);
	nvkm_vmm_flush_mark(it);
	return true;
}