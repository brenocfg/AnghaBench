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
struct nvkm_vmm {int dummy; } ;
struct nvkm_memory {int dummy; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int gp100_vmm_join (struct nvkm_vmm*,struct nvkm_memory*) ; 
 int lower_32_bits (int) ; 
 int /*<<< orphan*/  nvkm_done (struct nvkm_memory*) ; 
 int /*<<< orphan*/  nvkm_kmap (struct nvkm_memory*) ; 
 int nvkm_ro32 (struct nvkm_memory*,int) ; 
 int /*<<< orphan*/  nvkm_wo32 (struct nvkm_memory*,int,int) ; 
 int upper_32_bits (int) ; 

int
gv100_vmm_join(struct nvkm_vmm *vmm, struct nvkm_memory *inst)
{
	u64 data[2], mask;
	int ret = gp100_vmm_join(vmm, inst), i;
	if (ret)
		return ret;

	nvkm_kmap(inst);
	data[0] = nvkm_ro32(inst, 0x200);
	data[1] = nvkm_ro32(inst, 0x204);
	mask = BIT_ULL(0);

	nvkm_wo32(inst, 0x21c, 0x00000000);

	for (i = 0; i < 64; i++) {
		if (mask & BIT_ULL(i)) {
			nvkm_wo32(inst, 0x2a4 + (i * 0x10), data[1]);
			nvkm_wo32(inst, 0x2a0 + (i * 0x10), data[0]);
		} else {
			nvkm_wo32(inst, 0x2a4 + (i * 0x10), 0x00000001);
			nvkm_wo32(inst, 0x2a0 + (i * 0x10), 0x00000001);
		}
		nvkm_wo32(inst, 0x2a8 + (i * 0x10), 0x00000000);
	}

	nvkm_wo32(inst, 0x298, lower_32_bits(mask));
	nvkm_wo32(inst, 0x29c, upper_32_bits(mask));
	nvkm_done(inst);
	return 0;
}