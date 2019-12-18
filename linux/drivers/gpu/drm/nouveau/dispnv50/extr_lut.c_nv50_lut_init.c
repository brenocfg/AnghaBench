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
struct nvif_mmu {int dummy; } ;
struct nv50_lut {int /*<<< orphan*/ * mem; } ;
struct nv50_disp {TYPE_2__* disp; } ;
struct TYPE_3__ {scalar_t__ oclass; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ GF110_DISP ; 
 int /*<<< orphan*/  NVIF_MEM_VRAM ; 
 int nvif_mem_init_map (struct nvif_mmu*,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ *) ; 

int
nv50_lut_init(struct nv50_disp *disp, struct nvif_mmu *mmu,
	      struct nv50_lut *lut)
{
	const u32 size = disp->disp->object.oclass < GF110_DISP ? 257 : 1025;
	int i;
	for (i = 0; i < ARRAY_SIZE(lut->mem); i++) {
		int ret = nvif_mem_init_map(mmu, NVIF_MEM_VRAM, size * 8,
					    &lut->mem[i]);
		if (ret)
			return ret;
	}
	return 0;
}