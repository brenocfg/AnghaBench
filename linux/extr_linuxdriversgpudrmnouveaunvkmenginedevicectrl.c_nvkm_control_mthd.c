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
struct nvkm_object {int dummy; } ;
struct nvkm_control {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NVIF_CONTROL_PSTATE_ATTR 130 
#define  NVIF_CONTROL_PSTATE_INFO 129 
#define  NVIF_CONTROL_PSTATE_USER 128 
 struct nvkm_control* nvkm_control (struct nvkm_object*) ; 
 int nvkm_control_mthd_pstate_attr (struct nvkm_control*,void*,int) ; 
 int nvkm_control_mthd_pstate_info (struct nvkm_control*,void*,int) ; 
 int nvkm_control_mthd_pstate_user (struct nvkm_control*,void*,int) ; 

__attribute__((used)) static int
nvkm_control_mthd(struct nvkm_object *object, u32 mthd, void *data, u32 size)
{
	struct nvkm_control *ctrl = nvkm_control(object);
	switch (mthd) {
	case NVIF_CONTROL_PSTATE_INFO:
		return nvkm_control_mthd_pstate_info(ctrl, data, size);
	case NVIF_CONTROL_PSTATE_ATTR:
		return nvkm_control_mthd_pstate_attr(ctrl, data, size);
	case NVIF_CONTROL_PSTATE_USER:
		return nvkm_control_mthd_pstate_user(ctrl, data, size);
	default:
		break;
	}
	return -EINVAL;
}