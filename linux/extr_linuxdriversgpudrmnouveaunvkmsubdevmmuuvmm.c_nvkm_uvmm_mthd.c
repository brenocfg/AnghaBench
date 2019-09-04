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
struct nvkm_uvmm {int dummy; } ;
struct nvkm_object {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NVIF_VMM_V0_GET 132 
#define  NVIF_VMM_V0_MAP 131 
#define  NVIF_VMM_V0_PAGE 130 
#define  NVIF_VMM_V0_PUT 129 
#define  NVIF_VMM_V0_UNMAP 128 
 struct nvkm_uvmm* nvkm_uvmm (struct nvkm_object*) ; 
 int nvkm_uvmm_mthd_get (struct nvkm_uvmm*,void*,int) ; 
 int nvkm_uvmm_mthd_map (struct nvkm_uvmm*,void*,int) ; 
 int nvkm_uvmm_mthd_page (struct nvkm_uvmm*,void*,int) ; 
 int nvkm_uvmm_mthd_put (struct nvkm_uvmm*,void*,int) ; 
 int nvkm_uvmm_mthd_unmap (struct nvkm_uvmm*,void*,int) ; 

__attribute__((used)) static int
nvkm_uvmm_mthd(struct nvkm_object *object, u32 mthd, void *argv, u32 argc)
{
	struct nvkm_uvmm *uvmm = nvkm_uvmm(object);
	switch (mthd) {
	case NVIF_VMM_V0_PAGE  : return nvkm_uvmm_mthd_page  (uvmm, argv, argc);
	case NVIF_VMM_V0_GET   : return nvkm_uvmm_mthd_get   (uvmm, argv, argc);
	case NVIF_VMM_V0_PUT   : return nvkm_uvmm_mthd_put   (uvmm, argv, argc);
	case NVIF_VMM_V0_MAP   : return nvkm_uvmm_mthd_map   (uvmm, argv, argc);
	case NVIF_VMM_V0_UNMAP : return nvkm_uvmm_mthd_unmap (uvmm, argv, argc);
	default:
		break;
	}
	return -EINVAL;
}