#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nvif_mmu {TYPE_2__* type; } ;
struct TYPE_6__ {size_t* type_host; } ;
struct TYPE_4__ {struct nvif_mmu mmu; } ;
struct nouveau_drm {TYPE_3__ ttm; TYPE_1__ client; } ;
struct TYPE_5__ {int type; } ;

/* Variables and functions */
 int NVIF_MEM_UNCACHED ; 

__attribute__((used)) static inline bool
nouveau_drm_use_coherent_gpu_mapping(struct nouveau_drm *drm)
{
	struct nvif_mmu *mmu = &drm->client.mmu;
	return !(mmu->type[drm->ttm.type_host[0]].type & NVIF_MEM_UNCACHED);
}