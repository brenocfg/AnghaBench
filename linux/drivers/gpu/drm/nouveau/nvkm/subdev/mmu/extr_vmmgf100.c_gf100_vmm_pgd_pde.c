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
typedef  unsigned long long u64 ;
typedef  size_t u32 ;
struct nvkm_vmm_pt {struct nvkm_mmu_pt** pt; struct nvkm_vmm_pt** pde; } ;
struct nvkm_vmm {int dummy; } ;
struct nvkm_mmu_pt {int addr; int /*<<< orphan*/  memory; } ;

/* Variables and functions */
 unsigned long long BIT_ULL (int) ; 
#define  NVKM_MEM_TARGET_HOST 130 
#define  NVKM_MEM_TARGET_NCOH 129 
#define  NVKM_MEM_TARGET_VRAM 128 
 int /*<<< orphan*/  VMM_WO064 (struct nvkm_mmu_pt*,struct nvkm_vmm*,size_t,unsigned long long) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  nvkm_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_kmap (int /*<<< orphan*/ ) ; 
 int nvkm_memory_target (int /*<<< orphan*/ ) ; 

void
gf100_vmm_pgd_pde(struct nvkm_vmm *vmm, struct nvkm_vmm_pt *pgd, u32 pdei)
{
	struct nvkm_vmm_pt *pgt = pgd->pde[pdei];
	struct nvkm_mmu_pt *pd = pgd->pt[0];
	struct nvkm_mmu_pt *pt;
	u64 data = 0;

	if ((pt = pgt->pt[0])) {
		switch (nvkm_memory_target(pt->memory)) {
		case NVKM_MEM_TARGET_VRAM: data |= 1ULL << 0; break;
		case NVKM_MEM_TARGET_HOST: data |= 2ULL << 0;
			data |= BIT_ULL(35); /* VOL */
			break;
		case NVKM_MEM_TARGET_NCOH: data |= 3ULL << 0; break;
		default:
			WARN_ON(1);
			return;
		}
		data |= pt->addr >> 8;
	}

	if ((pt = pgt->pt[1])) {
		switch (nvkm_memory_target(pt->memory)) {
		case NVKM_MEM_TARGET_VRAM: data |= 1ULL << 32; break;
		case NVKM_MEM_TARGET_HOST: data |= 2ULL << 32;
			data |= BIT_ULL(34); /* VOL */
			break;
		case NVKM_MEM_TARGET_NCOH: data |= 3ULL << 32; break;
		default:
			WARN_ON(1);
			return;
		}
		data |= pt->addr << 24;
	}

	nvkm_kmap(pd->memory);
	VMM_WO064(pd, vmm, pdei * 8, data);
	nvkm_done(pd->memory);
}