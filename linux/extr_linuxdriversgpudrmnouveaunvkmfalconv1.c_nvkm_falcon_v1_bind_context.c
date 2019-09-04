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
typedef  int u32 ;
struct nvkm_memory {int dummy; } ;
struct nvkm_falcon {TYPE_1__* owner; } ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int FALCON_DMAIDX_PHYS_SYS_COH ; 
 int FALCON_DMAIDX_PHYS_SYS_NCOH ; 
 int FALCON_DMAIDX_PHYS_VID ; 
 int FALCON_DMAIDX_UCODE ; 
 int FALCON_DMAIDX_VIRT ; 
#define  NVKM_ENGINE_NVENC0 134 
#define  NVKM_ENGINE_NVENC1 133 
#define  NVKM_ENGINE_NVENC2 132 
#define  NVKM_MEM_TARGET_HOST 131 
#define  NVKM_MEM_TARGET_NCOH 130 
#define  NVKM_MEM_TARGET_VRAM 129 
#define  NVKM_SUBDEV_PMU 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  nvkm_falcon_mask (struct nvkm_falcon*,int,int,int) ; 
 int /*<<< orphan*/  nvkm_falcon_wr32 (struct nvkm_falcon*,int,int) ; 
 int nvkm_memory_addr (struct nvkm_memory*) ; 
 int nvkm_memory_target (struct nvkm_memory*) ; 

__attribute__((used)) static void
nvkm_falcon_v1_bind_context(struct nvkm_falcon *falcon, struct nvkm_memory *ctx)
{
	u32 inst_loc;
	u32 fbif;

	/* disable instance block binding */
	if (ctx == NULL) {
		nvkm_falcon_wr32(falcon, 0x10c, 0x0);
		return;
	}

	switch (falcon->owner->index) {
	case NVKM_ENGINE_NVENC0:
	case NVKM_ENGINE_NVENC1:
	case NVKM_ENGINE_NVENC2:
		fbif = 0x800;
		break;
	case NVKM_SUBDEV_PMU:
		fbif = 0xe00;
		break;
	default:
		fbif = 0x600;
		break;
	}

	nvkm_falcon_wr32(falcon, 0x10c, 0x1);

	/* setup apertures - virtual */
	nvkm_falcon_wr32(falcon, fbif + 4 * FALCON_DMAIDX_UCODE, 0x4);
	nvkm_falcon_wr32(falcon, fbif + 4 * FALCON_DMAIDX_VIRT, 0x0);
	/* setup apertures - physical */
	nvkm_falcon_wr32(falcon, fbif + 4 * FALCON_DMAIDX_PHYS_VID, 0x4);
	nvkm_falcon_wr32(falcon, fbif + 4 * FALCON_DMAIDX_PHYS_SYS_COH, 0x5);
	nvkm_falcon_wr32(falcon, fbif + 4 * FALCON_DMAIDX_PHYS_SYS_NCOH, 0x6);

	/* Set context */
	switch (nvkm_memory_target(ctx)) {
	case NVKM_MEM_TARGET_VRAM: inst_loc = 0; break;
	case NVKM_MEM_TARGET_HOST: inst_loc = 2; break;
	case NVKM_MEM_TARGET_NCOH: inst_loc = 3; break;
	default:
		WARN_ON(1);
		return;
	}

	/* Enable context */
	nvkm_falcon_mask(falcon, 0x048, 0x1, 0x1);
	nvkm_falcon_wr32(falcon, 0x054,
			 ((nvkm_memory_addr(ctx) >> 12) & 0xfffffff) |
			 (inst_loc << 28) | (1 << 30));

	nvkm_falcon_mask(falcon, 0x090, 0x10000, 0x10000);
	nvkm_falcon_mask(falcon, 0x0a4, 0x8, 0x8);
}