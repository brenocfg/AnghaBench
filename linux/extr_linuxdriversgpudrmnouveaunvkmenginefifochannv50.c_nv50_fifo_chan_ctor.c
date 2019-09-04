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
typedef  int /*<<< orphan*/  u64 ;
struct nvkm_oclass {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  inst; } ;
struct nv50_fifo_chan {int /*<<< orphan*/  ramht; TYPE_4__ base; int /*<<< orphan*/  pgd; int /*<<< orphan*/  eng; int /*<<< orphan*/  ramfc; struct nv50_fifo* fifo; } ;
struct TYPE_5__ {struct nvkm_device* device; } ;
struct TYPE_6__ {TYPE_1__ subdev; } ;
struct TYPE_7__ {TYPE_2__ engine; } ;
struct nv50_fifo {TYPE_3__ base; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long long NVKM_ENGINE_DMAOBJ ; 
 unsigned long long NVKM_ENGINE_GR ; 
 unsigned long long NVKM_ENGINE_MPEG ; 
 unsigned long long NVKM_ENGINE_SW ; 
 int /*<<< orphan*/  nv50_fifo_chan_func ; 
 int nvkm_fifo_chan_ctor (int /*<<< orphan*/ *,TYPE_3__*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,int,int,struct nvkm_oclass const*,TYPE_4__*) ; 
 int nvkm_gpuobj_new (struct nvkm_device*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nvkm_ramht_new (struct nvkm_device*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
nv50_fifo_chan_ctor(struct nv50_fifo *fifo, u64 vmm, u64 push,
		    const struct nvkm_oclass *oclass,
		    struct nv50_fifo_chan *chan)
{
	struct nvkm_device *device = fifo->base.engine.subdev.device;
	int ret;

	if (!vmm)
		return -EINVAL;

	ret = nvkm_fifo_chan_ctor(&nv50_fifo_chan_func, &fifo->base,
				  0x10000, 0x1000, false, vmm, push,
				  (1ULL << NVKM_ENGINE_DMAOBJ) |
				  (1ULL << NVKM_ENGINE_SW) |
				  (1ULL << NVKM_ENGINE_GR) |
				  (1ULL << NVKM_ENGINE_MPEG),
				  0, 0xc00000, 0x2000, oclass, &chan->base);
	chan->fifo = fifo;
	if (ret)
		return ret;

	ret = nvkm_gpuobj_new(device, 0x0200, 0x1000, true, chan->base.inst,
			      &chan->ramfc);
	if (ret)
		return ret;

	ret = nvkm_gpuobj_new(device, 0x1200, 0, true, chan->base.inst,
			      &chan->eng);
	if (ret)
		return ret;

	ret = nvkm_gpuobj_new(device, 0x4000, 0, false, chan->base.inst,
			      &chan->pgd);
	if (ret)
		return ret;

	return nvkm_ramht_new(device, 0x8000, 16, chan->base.inst, &chan->ramht);
}