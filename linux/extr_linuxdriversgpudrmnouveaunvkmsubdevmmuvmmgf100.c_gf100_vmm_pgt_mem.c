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
struct nvkm_vmm_map {int dummy; } ;
struct nvkm_vmm {int dummy; } ;
struct nvkm_mmu_pt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMM_MAP_ITER_MEM (struct nvkm_vmm*,struct nvkm_mmu_pt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nvkm_vmm_map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gf100_vmm_pgt_pte ; 

void
gf100_vmm_pgt_mem(struct nvkm_vmm *vmm, struct nvkm_mmu_pt *pt,
		  u32 ptei, u32 ptes, struct nvkm_vmm_map *map)
{
	VMM_MAP_ITER_MEM(vmm, pt, ptei, ptes, map, gf100_vmm_pgt_pte);
}