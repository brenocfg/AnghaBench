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
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct nvkm_vmm_pt {struct nvkm_mmu_pt** pt; struct nvkm_vmm_pt** pde; } ;
struct nvkm_vmm {int dummy; } ;
struct nvkm_mmu_pt {int /*<<< orphan*/  memory; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMM_WO064 (struct nvkm_mmu_pt*,struct nvkm_vmm*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gp100_vmm_pde (struct nvkm_mmu_pt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_kmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gp100_vmm_pd1_pde(struct nvkm_vmm *vmm, struct nvkm_vmm_pt *pgd, u32 pdei)
{
	struct nvkm_vmm_pt *pgt = pgd->pde[pdei];
	struct nvkm_mmu_pt *pd = pgd->pt[0];
	u64 data = 0;

	if (!gp100_vmm_pde(pgt->pt[0], &data))
		return;

	nvkm_kmap(pd->memory);
	VMM_WO064(pd, vmm, pdei * 8, data);
	nvkm_done(pd->memory);
}