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
struct TYPE_4__ {int /*<<< orphan*/  (* invalid ) (struct nvkm_vmm*,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  (* sparse ) (struct nvkm_vmm*,int /*<<< orphan*/ ,int,int) ;} ;
struct TYPE_3__ {struct nvkm_vmm_desc* desc; } ;

/* Variables and functions */
 int NVKM_VMM_PTE_SPARSE ; 
 int NVKM_VMM_PTE_SPTES ; 
 int NVKM_VMM_PTE_VALID ; 
 int /*<<< orphan*/  TRA (struct nvkm_vmm_iter*,char*,int,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_vmm*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub2 (struct nvkm_vmm*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
nvkm_vmm_unref_sptes(struct nvkm_vmm_iter *it, struct nvkm_vmm_pt *pgt,
		     const struct nvkm_vmm_desc *desc, u32 ptei, u32 ptes)
{
	const struct nvkm_vmm_desc *pair = it->page[-1].desc;
	const u32 sptb = desc->bits - pair->bits;
	const u32 sptn = 1 << sptb;
	struct nvkm_vmm *vmm = it->vmm;
	u32 spti = ptei & (sptn - 1), lpti, pteb;

	/* Determine how many SPTEs are being touched under each LPTE,
	 * and drop reference counts.
	 */
	for (lpti = ptei >> sptb; ptes; spti = 0, lpti++) {
		const u32 pten = min(sptn - spti, ptes);
		pgt->pte[lpti] -= pten;
		ptes -= pten;
	}

	/* We're done here if there's no corresponding LPT. */
	if (!pgt->refs[0])
		return;

	for (ptei = pteb = ptei >> sptb; ptei < lpti; pteb = ptei) {
		/* Skip over any LPTEs that still have valid SPTEs. */
		if (pgt->pte[pteb] & NVKM_VMM_PTE_SPTES) {
			for (ptes = 1, ptei++; ptei < lpti; ptes++, ptei++) {
				if (!(pgt->pte[ptei] & NVKM_VMM_PTE_SPTES))
					break;
			}
			continue;
		}

		/* As there's no more non-UNMAPPED SPTEs left in the range
		 * covered by a number of LPTEs, the LPTEs once again take
		 * control over their address range.
		 *
		 * Determine how many LPTEs need to transition state.
		 */
		pgt->pte[ptei] &= ~NVKM_VMM_PTE_VALID;
		for (ptes = 1, ptei++; ptei < lpti; ptes++, ptei++) {
			if (pgt->pte[ptei] & NVKM_VMM_PTE_SPTES)
				break;
			pgt->pte[ptei] &= ~NVKM_VMM_PTE_VALID;
		}

		if (pgt->pte[pteb] & NVKM_VMM_PTE_SPARSE) {
			TRA(it, "LPTE %05x: U -> S %d PTEs", pteb, ptes);
			pair->func->sparse(vmm, pgt->pt[0], pteb, ptes);
		} else
		if (pair->func->invalid) {
			/* If the MMU supports it, restore the LPTE to the
			 * INVALID state to tell the MMU there is no point
			 * trying to fetch the corresponding SPTEs.
			 */
			TRA(it, "LPTE %05x: U -> I %d PTEs", pteb, ptes);
			pair->func->invalid(vmm, pgt->pt[0], pteb, ptes);
		}
	}
}