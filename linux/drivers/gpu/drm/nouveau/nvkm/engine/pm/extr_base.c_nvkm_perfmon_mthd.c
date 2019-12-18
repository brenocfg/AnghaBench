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
struct nvkm_perfmon {int dummy; } ;
struct nvkm_object {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NVIF_PERFMON_V0_QUERY_DOMAIN 130 
#define  NVIF_PERFMON_V0_QUERY_SIGNAL 129 
#define  NVIF_PERFMON_V0_QUERY_SOURCE 128 
 struct nvkm_perfmon* nvkm_perfmon (struct nvkm_object*) ; 
 int nvkm_perfmon_mthd_query_domain (struct nvkm_perfmon*,void*,int) ; 
 int nvkm_perfmon_mthd_query_signal (struct nvkm_perfmon*,void*,int) ; 
 int nvkm_perfmon_mthd_query_source (struct nvkm_perfmon*,void*,int) ; 

__attribute__((used)) static int
nvkm_perfmon_mthd(struct nvkm_object *object, u32 mthd, void *data, u32 size)
{
	struct nvkm_perfmon *perfmon = nvkm_perfmon(object);
	switch (mthd) {
	case NVIF_PERFMON_V0_QUERY_DOMAIN:
		return nvkm_perfmon_mthd_query_domain(perfmon, data, size);
	case NVIF_PERFMON_V0_QUERY_SIGNAL:
		return nvkm_perfmon_mthd_query_signal(perfmon, data, size);
	case NVIF_PERFMON_V0_QUERY_SOURCE:
		return nvkm_perfmon_mthd_query_source(perfmon, data, size);
	default:
		break;
	}
	return -EINVAL;
}