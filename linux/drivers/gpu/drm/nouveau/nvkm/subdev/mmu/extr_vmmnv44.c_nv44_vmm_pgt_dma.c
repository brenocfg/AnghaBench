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
struct nvkm_vmm_map {int const dma; } ;
struct nvkm_vmm {int dummy; } ;
struct nvkm_mmu_pt {int /*<<< orphan*/  memory; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMM_MAP_ITER_DMA (struct nvkm_vmm*,struct nvkm_mmu_pt*,int,int,struct nvkm_vmm_map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMM_WO032 (struct nvkm_mmu_pt*,struct nvkm_vmm*,int,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  nv44_vmm_pgt_fill (struct nvkm_vmm*,struct nvkm_mmu_pt*,int const,int,int const) ; 
 int /*<<< orphan*/  nv44_vmm_pgt_pte ; 
 int /*<<< orphan*/  nvkm_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_kmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nv44_vmm_pgt_dma(struct nvkm_vmm *vmm, struct nvkm_mmu_pt *pt,
		 u32 ptei, u32 ptes, struct nvkm_vmm_map *map)
{
#if PAGE_SHIFT == 12
	nvkm_kmap(pt->memory);
	if (ptei & 3) {
		const u32 pten = min(ptes, 4 - (ptei & 3));
		nv44_vmm_pgt_fill(vmm, pt, map->dma, ptei, pten);
		ptei += pten;
		ptes -= pten;
		map->dma += pten;
	}

	while (ptes >= 4) {
		u32 tmp[4], i;
		for (i = 0; i < 4; i++)
			tmp[i] = *map->dma++ >> 12;
		VMM_WO032(pt, vmm, ptei++ * 4, tmp[0] >>  0 | tmp[1] << 27);
		VMM_WO032(pt, vmm, ptei++ * 4, tmp[1] >>  5 | tmp[2] << 22);
		VMM_WO032(pt, vmm, ptei++ * 4, tmp[2] >> 10 | tmp[3] << 17);
		VMM_WO032(pt, vmm, ptei++ * 4, tmp[3] >> 15 | 0x40000000);
		ptes -= 4;
	}

	if (ptes) {
		nv44_vmm_pgt_fill(vmm, pt, map->dma, ptei, ptes);
		map->dma += ptes;
	}
	nvkm_done(pt->memory);
#else
	VMM_MAP_ITER_DMA(vmm, pt, ptei, ptes, map, nv44_vmm_pgt_pte);
#endif
}