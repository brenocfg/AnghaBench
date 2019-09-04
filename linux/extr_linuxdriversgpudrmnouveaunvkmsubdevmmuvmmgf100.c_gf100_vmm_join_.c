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
typedef  unsigned long long u64 ;
struct nvkm_vmm {unsigned long long limit; TYPE_1__* pd; } ;
struct nvkm_mmu_pt {unsigned long long addr; int /*<<< orphan*/  memory; } ;
struct nvkm_memory {int dummy; } ;
struct TYPE_2__ {struct nvkm_mmu_pt** pt; } ;

/* Variables and functions */
 unsigned long long BIT_ULL (int) ; 
 int EINVAL ; 
#define  NVKM_MEM_TARGET_HOST 130 
#define  NVKM_MEM_TARGET_NCOH 129 
#define  NVKM_MEM_TARGET_VRAM 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  nvkm_done (struct nvkm_memory*) ; 
 int /*<<< orphan*/  nvkm_kmap (struct nvkm_memory*) ; 
 int nvkm_memory_target (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_wo64 (struct nvkm_memory*,int,unsigned long long) ; 

int
gf100_vmm_join_(struct nvkm_vmm *vmm, struct nvkm_memory *inst, u64 base)
{
	struct nvkm_mmu_pt *pd = vmm->pd->pt[0];

	switch (nvkm_memory_target(pd->memory)) {
	case NVKM_MEM_TARGET_VRAM: base |= 0ULL << 0; break;
	case NVKM_MEM_TARGET_HOST: base |= 2ULL << 0;
		base |= BIT_ULL(2) /* VOL. */;
		break;
	case NVKM_MEM_TARGET_NCOH: base |= 3ULL << 0; break;
	default:
		WARN_ON(1);
		return -EINVAL;
	}
	base |= pd->addr;

	nvkm_kmap(inst);
	nvkm_wo64(inst, 0x0200, base);
	nvkm_wo64(inst, 0x0208, vmm->limit - 1);
	nvkm_done(inst);
	return 0;
}