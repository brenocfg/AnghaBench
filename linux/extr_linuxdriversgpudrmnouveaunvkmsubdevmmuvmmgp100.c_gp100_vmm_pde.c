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
struct nvkm_mmu_pt {int addr; int /*<<< orphan*/  memory; } ;

/* Variables and functions */
 unsigned long long BIT_ULL (int) ; 
#define  NVKM_MEM_TARGET_HOST 130 
#define  NVKM_MEM_TARGET_NCOH 129 
#define  NVKM_MEM_TARGET_VRAM 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int nvkm_memory_target (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
gp100_vmm_pde(struct nvkm_mmu_pt *pt, u64 *data)
{
	switch (nvkm_memory_target(pt->memory)) {
	case NVKM_MEM_TARGET_VRAM: *data |= 1ULL << 1; break;
	case NVKM_MEM_TARGET_HOST: *data |= 2ULL << 1;
		*data |= BIT_ULL(3); /* VOL. */
		break;
	case NVKM_MEM_TARGET_NCOH: *data |= 3ULL << 1; break;
	default:
		WARN_ON(1);
		return false;
	}
	*data |= pt->addr >> 4;
	return true;
}