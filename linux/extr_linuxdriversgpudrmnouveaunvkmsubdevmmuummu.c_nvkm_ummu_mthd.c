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
typedef  int u32 ;
struct nvkm_ummu {int dummy; } ;
struct nvkm_object {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NVIF_MMU_V0_HEAP 130 
#define  NVIF_MMU_V0_KIND 129 
#define  NVIF_MMU_V0_TYPE 128 
 struct nvkm_ummu* nvkm_ummu (struct nvkm_object*) ; 
 int nvkm_ummu_heap (struct nvkm_ummu*,void*,int) ; 
 int nvkm_ummu_kind (struct nvkm_ummu*,void*,int) ; 
 int nvkm_ummu_type (struct nvkm_ummu*,void*,int) ; 

__attribute__((used)) static int
nvkm_ummu_mthd(struct nvkm_object *object, u32 mthd, void *argv, u32 argc)
{
	struct nvkm_ummu *ummu = nvkm_ummu(object);
	switch (mthd) {
	case NVIF_MMU_V0_HEAP: return nvkm_ummu_heap(ummu, argv, argc);
	case NVIF_MMU_V0_TYPE: return nvkm_ummu_type(ummu, argv, argc);
	case NVIF_MMU_V0_KIND: return nvkm_ummu_kind(ummu, argv, argc);
	default:
		break;
	}
	return -EINVAL;
}