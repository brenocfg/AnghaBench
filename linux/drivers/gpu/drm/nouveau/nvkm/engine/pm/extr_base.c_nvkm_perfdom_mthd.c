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
struct nvkm_perfdom {int dummy; } ;
struct nvkm_object {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NVIF_PERFDOM_V0_INIT 130 
#define  NVIF_PERFDOM_V0_READ 129 
#define  NVIF_PERFDOM_V0_SAMPLE 128 
 struct nvkm_perfdom* nvkm_perfdom (struct nvkm_object*) ; 
 int nvkm_perfdom_init (struct nvkm_perfdom*,void*,int) ; 
 int nvkm_perfdom_read (struct nvkm_perfdom*,void*,int) ; 
 int nvkm_perfdom_sample (struct nvkm_perfdom*,void*,int) ; 

__attribute__((used)) static int
nvkm_perfdom_mthd(struct nvkm_object *object, u32 mthd, void *data, u32 size)
{
	struct nvkm_perfdom *dom = nvkm_perfdom(object);
	switch (mthd) {
	case NVIF_PERFDOM_V0_INIT:
		return nvkm_perfdom_init(dom, data, size);
	case NVIF_PERFDOM_V0_SAMPLE:
		return nvkm_perfdom_sample(dom, data, size);
	case NVIF_PERFDOM_V0_READ:
		return nvkm_perfdom_read(dom, data, size);
	default:
		break;
	}
	return -EINVAL;
}