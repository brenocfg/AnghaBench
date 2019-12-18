#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nvkm_vmm_pt {int* pte; int /*<<< orphan*/ * pt; int /*<<< orphan*/ * refs; } ;
struct nvkm_vmm_iter {struct nvkm_vmm* vmm; TYPE_1__* page; } ;
struct nvkm_vmm_desc {int bits; TYPE_2__* func; } ;
struct nvkm_vmm {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* unmap ) (struct nvkm_vmm*,int /*<<< orphan*/ ,int,int) ;scalar_t__ invalid; int /*<<< orphan*/  (* sparse ) (struct nvkm_vmm*,int /*<<< orphan*/ ,int const,int const) ;} ;
struct TYPE_3__ {struct nvkm_vmm_desc* desc; } ;

/* Variables and functions */
 int NVKM_VMM_PTE_SPARSE ; 
 int NVKM_VMM_PTE_VALID ; 
 int /*<<< orphan*/  TRA (struct nvkm_vmm_iter*,char*,int const,int const) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_vmm*,int /*<<< orphan*/ ,int const,int const) ; 
 int /*<<< orphan*/  stub2 (struct nvkm_vmm*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub3 (struct nvkm_vmm*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
nvkm_vmm_ref_sptes(struct nvkm_vmm_iter *it, struct nvkm_vmm_pt *pgt,
		   const struct nvkm_vmm_desc *desc, u32 ptei, u32 ptes)
{
	const struct nvkm_vmm_desc *pair = it->page[-1].desc;
	const u32 sptb = desc->bits - pair->bits;
	const u32 sptn = 1 << sptb;
	struct nvkm_vmm *vmm = it->vmm;
	u32 spti = ptei & (sptn - 1), lpti, pteb;

	/* Determine how many SPTEs are being touched under each LPTE,
	 * and increase reference counts.
	 */
	for (lpti = ptei >> sptb; ptes; spti = 0, lpti++) {
		const u32 pten = min(sptn - spti, ptes);
		pgt->pte[lpti] += pten;
		ptes -= pten;
	}

	/* We're done here if there's no corresponding LPT. */
	if (!pgt->refs[0])
		return;

	for (ptei = pteb = ptei >> sptb; ptei < lpti; pteb = ptei) {
		/* Skip over any LPTEs that already have valid SPTEs. */
		if (pgt->pte[pteb] & NVKM_VMM_PTE_VALID) {
			for (ptes = 1, ptei++; ptei < lpti; ptes++, ptei++) {
				if (!(pgt->pte[ptei] & NVKM_VMM_PTE_VALID))
					break;
			}
			continue;
		}

		/* As there are now non-UNMAPPED SPTEs in the range covered
		 * by a number of LPTEs, we need to transfer control of the
		 * address range to the SPTEs.
		 *
		 * Determine how many LPTEs need to transition state.
		 */
		pgt->pte[ptei] |= NVKM_VMM_PTE_VALID;
		for (ptes = 1, ptei++; ptei < lpti; ptes++, ptei++) {
			if (pgt->pte[ptei] & NVKM_VMM_PTE_VALID)
				break;
			pgt->pte[ptei] |= NVKM_VMM_PTE_VALID;
		}

		if (pgt->pte[pteb] & NVKM_VMM_PTE_SPARSE) {
			const u32 spti = pteb * sptn;
			const u32 sptc = ptes * sptn;
			/* The entire LPTE is marked as sparse, we need
			 * to make sure that the SPTEs are too.
			 */
			TRA(it, "SPTE %05x: U -> S %d PTEs", spti, sptc);
			desc->func->sparse(vmm, pgt->pt[1], spti, sptc);
			/* Sparse LPTEs prevent SPTEs from being accessed. */
			TRA(it, "LPTE %05x: S -> U %d PTEs", pteb, ptes);
			pair->func->unmap(vmm, pgt->pt[0], pteb, ptes);
		} else
		if (pair->func->invalid) {
			/* MMU supports blocking SPTEs by marking an LPTE
			 * as INVALID.  We need to reverse that here.
			 */
			TRA(it, "LPTE %05x: I -> U %d PTEs", pteb, ptes);
			pair->func->unmap(vmm, pgt->pt[0], pteb, ptes);
		}
	}
}