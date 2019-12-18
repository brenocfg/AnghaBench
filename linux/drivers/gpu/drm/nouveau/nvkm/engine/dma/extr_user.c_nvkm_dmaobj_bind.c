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
struct nvkm_object {int dummy; } ;
struct nvkm_gpuobj {int dummy; } ;
struct nvkm_dmaobj {TYPE_1__* func; } ;
struct TYPE_2__ {int (* bind ) (struct nvkm_dmaobj*,struct nvkm_gpuobj*,int,struct nvkm_gpuobj**) ;} ;

/* Variables and functions */
 struct nvkm_dmaobj* nvkm_dmaobj (struct nvkm_object*) ; 
 int stub1 (struct nvkm_dmaobj*,struct nvkm_gpuobj*,int,struct nvkm_gpuobj**) ; 

__attribute__((used)) static int
nvkm_dmaobj_bind(struct nvkm_object *base, struct nvkm_gpuobj *gpuobj,
		 int align, struct nvkm_gpuobj **pgpuobj)
{
	struct nvkm_dmaobj *dmaobj = nvkm_dmaobj(base);
	return dmaobj->func->bind(dmaobj, gpuobj, align, pgpuobj);
}