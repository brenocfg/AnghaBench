#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nvkm_object {int dummy; } ;
struct nvkm_gpuobj {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  device; } ;
struct TYPE_6__ {TYPE_1__ subdev; } ;
struct TYPE_7__ {TYPE_2__ engine; } ;
struct nv50_gr {TYPE_3__ base; int /*<<< orphan*/  size; } ;
struct TYPE_8__ {struct nv50_gr* gr; } ;

/* Variables and functions */
 TYPE_4__* nv50_gr_chan (struct nvkm_object*) ; 
 int /*<<< orphan*/  nv50_grctx_fill (int /*<<< orphan*/ ,struct nvkm_gpuobj*) ; 
 int /*<<< orphan*/  nvkm_done (struct nvkm_gpuobj*) ; 
 int nvkm_gpuobj_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct nvkm_gpuobj*,struct nvkm_gpuobj**) ; 
 int /*<<< orphan*/  nvkm_kmap (struct nvkm_gpuobj*) ; 

__attribute__((used)) static int
nv50_gr_chan_bind(struct nvkm_object *object, struct nvkm_gpuobj *parent,
		  int align, struct nvkm_gpuobj **pgpuobj)
{
	struct nv50_gr *gr = nv50_gr_chan(object)->gr;
	int ret = nvkm_gpuobj_new(gr->base.engine.subdev.device, gr->size,
				  align, true, parent, pgpuobj);
	if (ret == 0) {
		nvkm_kmap(*pgpuobj);
		nv50_grctx_fill(gr->base.engine.subdev.device, *pgpuobj);
		nvkm_done(*pgpuobj);
	}
	return ret;
}