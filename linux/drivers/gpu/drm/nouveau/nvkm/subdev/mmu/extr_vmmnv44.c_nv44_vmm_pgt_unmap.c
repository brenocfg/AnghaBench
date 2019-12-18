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
typedef  int u32 ;
struct nvkm_vmm {int dummy; } ;
struct nvkm_mmu_pt {int /*<<< orphan*/  memory; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMM_WO032 (struct nvkm_mmu_pt*,struct nvkm_vmm*,int,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  nv44_vmm_pgt_fill (struct nvkm_vmm*,struct nvkm_mmu_pt*,int /*<<< orphan*/ *,int,int const) ; 
 int /*<<< orphan*/  nvkm_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_kmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nv44_vmm_pgt_unmap(struct nvkm_vmm *vmm,
		   struct nvkm_mmu_pt *pt, u32 ptei, u32 ptes)
{
	nvkm_kmap(pt->memory);
	if (ptei & 3) {
		const u32 pten = min(ptes, 4 - (ptei & 3));
		nv44_vmm_pgt_fill(vmm, pt, NULL, ptei, pten);
		ptei += pten;
		ptes -= pten;
	}

	while (ptes > 4) {
		VMM_WO032(pt, vmm, ptei++ * 4, 0x00000000);
		VMM_WO032(pt, vmm, ptei++ * 4, 0x00000000);
		VMM_WO032(pt, vmm, ptei++ * 4, 0x00000000);
		VMM_WO032(pt, vmm, ptei++ * 4, 0x00000000);
		ptes -= 4;
	}

	if (ptes)
		nv44_vmm_pgt_fill(vmm, pt, NULL, ptei, ptes);
	nvkm_done(pt->memory);
}