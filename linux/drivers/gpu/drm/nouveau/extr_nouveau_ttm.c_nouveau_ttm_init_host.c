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
typedef  int u8 ;
struct nvif_mmu {int dummy; } ;
struct TYPE_3__ {int* type_host; int* type_ncoh; } ;
struct TYPE_4__ {struct nvif_mmu mmu; } ;
struct nouveau_drm {TYPE_1__ ttm; TYPE_2__ client; } ;

/* Variables and functions */
 int ENOSYS ; 
 int NVIF_MEM_COHERENT ; 
 int NVIF_MEM_HOST ; 
 int NVIF_MEM_MAPPABLE ; 
 int nvif_mmu_type (struct nvif_mmu*,int) ; 

__attribute__((used)) static int
nouveau_ttm_init_host(struct nouveau_drm *drm, u8 kind)
{
	struct nvif_mmu *mmu = &drm->client.mmu;
	int typei;

	typei = nvif_mmu_type(mmu, NVIF_MEM_HOST | NVIF_MEM_MAPPABLE |
					    kind | NVIF_MEM_COHERENT);
	if (typei < 0)
		return -ENOSYS;

	drm->ttm.type_host[!!kind] = typei;

	typei = nvif_mmu_type(mmu, NVIF_MEM_HOST | NVIF_MEM_MAPPABLE | kind);
	if (typei < 0)
		return -ENOSYS;

	drm->ttm.type_ncoh[!!kind] = typei;
	return 0;
}