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
typedef  int u64 ;
typedef  int u32 ;
struct nvkm_vmm_map {int type; int ctag; unsigned long long next; } ;
struct nvkm_vmm {int dummy; } ;
struct nvkm_mmu_pt {int dummy; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int /*<<< orphan*/  VMM_WO064 (struct nvkm_mmu_pt*,struct nvkm_vmm*,int,int) ; 

__attribute__((used)) static inline void
gf100_vmm_pgt_pte(struct nvkm_vmm *vmm, struct nvkm_mmu_pt *pt,
		  u32 ptei, u32 ptes, struct nvkm_vmm_map *map, u64 addr)
{
	u64 base = (addr >> 8) | map->type;
	u64 data = base;

	if (map->ctag && !(map->next & (1ULL << 44))) {
		while (ptes--) {
			data = base | ((map->ctag >> 1) << 44);
			if (!(map->ctag++ & 1))
				data |= BIT_ULL(60);

			VMM_WO064(pt, vmm, ptei++ * 8, data);
			base += map->next;
		}
	} else {
		map->type += ptes * map->ctag;

		while (ptes--) {
			VMM_WO064(pt, vmm, ptei++ * 8, data);
			data += map->next;
		}
	}
}