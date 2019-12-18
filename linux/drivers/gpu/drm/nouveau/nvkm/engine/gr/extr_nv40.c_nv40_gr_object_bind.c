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
struct nvkm_object {int oclass; TYPE_2__* engine; } ;
struct nvkm_gpuobj {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_done (struct nvkm_gpuobj*) ; 
 int nvkm_gpuobj_new (int /*<<< orphan*/ ,int,int,int,struct nvkm_gpuobj*,struct nvkm_gpuobj**) ; 
 int /*<<< orphan*/  nvkm_kmap (struct nvkm_gpuobj*) ; 
 int /*<<< orphan*/  nvkm_mo32 (struct nvkm_gpuobj*,int,int,int) ; 
 int /*<<< orphan*/  nvkm_wo32 (struct nvkm_gpuobj*,int,int) ; 

__attribute__((used)) static int
nv40_gr_object_bind(struct nvkm_object *object, struct nvkm_gpuobj *parent,
		    int align, struct nvkm_gpuobj **pgpuobj)
{
	int ret = nvkm_gpuobj_new(object->engine->subdev.device, 20, align,
				  false, parent, pgpuobj);
	if (ret == 0) {
		nvkm_kmap(*pgpuobj);
		nvkm_wo32(*pgpuobj, 0x00, object->oclass);
		nvkm_wo32(*pgpuobj, 0x04, 0x00000000);
		nvkm_wo32(*pgpuobj, 0x08, 0x00000000);
#ifdef __BIG_ENDIAN
		nvkm_mo32(*pgpuobj, 0x08, 0x01000000, 0x01000000);
#endif
		nvkm_wo32(*pgpuobj, 0x0c, 0x00000000);
		nvkm_wo32(*pgpuobj, 0x10, 0x00000000);
		nvkm_done(*pgpuobj);
	}
	return ret;
}