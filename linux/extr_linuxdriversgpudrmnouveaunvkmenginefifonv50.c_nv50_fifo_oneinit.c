#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nvkm_fifo {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;
struct nv50_fifo {int /*<<< orphan*/ * runlist; TYPE_3__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVKM_MEM_TARGET_INST ; 
 struct nv50_fifo* nv50_fifo (struct nvkm_fifo*) ; 
 int nvkm_memory_new (struct nvkm_device*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ; 

int
nv50_fifo_oneinit(struct nvkm_fifo *base)
{
	struct nv50_fifo *fifo = nv50_fifo(base);
	struct nvkm_device *device = fifo->base.engine.subdev.device;
	int ret;

	ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST, 128 * 4, 0x1000,
			      false, &fifo->runlist[0]);
	if (ret)
		return ret;

	return nvkm_memory_new(device, NVKM_MEM_TARGET_INST, 128 * 4, 0x1000,
			       false, &fifo->runlist[1]);
}