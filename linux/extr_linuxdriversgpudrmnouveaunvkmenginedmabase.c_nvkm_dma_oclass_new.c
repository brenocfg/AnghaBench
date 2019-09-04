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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_oclass {int /*<<< orphan*/  engine; } ;
struct nvkm_object {int dummy; } ;
struct nvkm_dmaobj {struct nvkm_object object; } ;
struct nvkm_dma {TYPE_1__* func; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_2__ {int (* class_new ) (struct nvkm_dma*,struct nvkm_oclass const*,void*,int /*<<< orphan*/ ,struct nvkm_dmaobj**) ;} ;

/* Variables and functions */
 struct nvkm_dma* nvkm_dma (int /*<<< orphan*/ ) ; 
 int stub1 (struct nvkm_dma*,struct nvkm_oclass const*,void*,int /*<<< orphan*/ ,struct nvkm_dmaobj**) ; 

__attribute__((used)) static int
nvkm_dma_oclass_new(struct nvkm_device *device,
		    const struct nvkm_oclass *oclass, void *data, u32 size,
		    struct nvkm_object **pobject)
{
	struct nvkm_dma *dma = nvkm_dma(oclass->engine);
	struct nvkm_dmaobj *dmaobj = NULL;
	int ret;

	ret = dma->func->class_new(dma, oclass, data, size, &dmaobj);
	if (dmaobj)
		*pobject = &dmaobj->object;
	return ret;
}