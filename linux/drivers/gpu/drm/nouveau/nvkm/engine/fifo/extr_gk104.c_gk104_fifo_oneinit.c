#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nvkm_vmm {int dummy; } ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_fifo {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_16__ {int /*<<< orphan*/  bar; int /*<<< orphan*/  mem; } ;
struct TYPE_9__ {struct nvkm_subdev subdev; } ;
struct TYPE_15__ {int nr; TYPE_1__ engine; } ;
struct gk104_fifo {int pbdma_nr; int engine_nr; int runlist_nr; TYPE_8__ user; TYPE_7__ base; TYPE_6__* runlist; TYPE_5__* func; TYPE_3__* engine; } ;
typedef  enum nvkm_devidx { ____Placeholder_nvkm_devidx } nvkm_devidx ;
struct TYPE_14__ {int engm; int /*<<< orphan*/  chan; int /*<<< orphan*/  cgrp; int /*<<< orphan*/  wait; int /*<<< orphan*/ * mem; } ;
struct TYPE_13__ {TYPE_4__* runlist; TYPE_2__* pbdma; } ;
struct TYPE_12__ {int size; } ;
struct TYPE_11__ {int runl; int pbid; int /*<<< orphan*/  engine; } ;
struct TYPE_10__ {int (* nr ) (struct gk104_fifo*) ;} ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NVKM_MEM_TARGET_INST ; 
 struct gk104_fifo* gk104_fifo (struct nvkm_fifo*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 void* max (int,int) ; 
 struct nvkm_vmm* nvkm_bar_bar1_vmm (struct nvkm_device*) ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*,int,...) ; 
 int /*<<< orphan*/  nvkm_device_engine (struct nvkm_device*,int) ; 
 int nvkm_memory_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nvkm_vmm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nvkm_memory_new (struct nvkm_device*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_memory_size (int /*<<< orphan*/ ) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/ * nvkm_subdev_name ; 
 int nvkm_top_engine (struct nvkm_device*,int /*<<< orphan*/ ,int*,int*) ; 
 int nvkm_vmm_get (struct nvkm_vmm*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct gk104_fifo*) ; 

__attribute__((used)) static int
gk104_fifo_oneinit(struct nvkm_fifo *base)
{
	struct gk104_fifo *fifo = gk104_fifo(base);
	struct nvkm_subdev *subdev = &fifo->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	struct nvkm_vmm *bar = nvkm_bar_bar1_vmm(device);
	int engn, runl, pbid, ret, i, j;
	enum nvkm_devidx engidx;
	u32 *map;

	fifo->pbdma_nr = fifo->func->pbdma->nr(fifo);
	nvkm_debug(subdev, "%d PBDMA(s)\n", fifo->pbdma_nr);

	/* Read PBDMA->runlist(s) mapping from HW. */
	if (!(map = kcalloc(fifo->pbdma_nr, sizeof(*map), GFP_KERNEL)))
		return -ENOMEM;

	for (i = 0; i < fifo->pbdma_nr; i++)
		map[i] = nvkm_rd32(device, 0x002390 + (i * 0x04));

	/* Determine runlist configuration from topology device info. */
	i = 0;
	while ((int)(engidx = nvkm_top_engine(device, i++, &runl, &engn)) >= 0) {
		/* Determine which PBDMA handles requests for this engine. */
		for (j = 0, pbid = -1; j < fifo->pbdma_nr; j++) {
			if (map[j] & (1 << runl)) {
				pbid = j;
				break;
			}
		}

		nvkm_debug(subdev, "engine %2d: runlist %2d pbdma %2d (%s)\n",
			   engn, runl, pbid, nvkm_subdev_name[engidx]);

		fifo->engine[engn].engine = nvkm_device_engine(device, engidx);
		fifo->engine[engn].runl = runl;
		fifo->engine[engn].pbid = pbid;
		fifo->engine_nr = max(fifo->engine_nr, engn + 1);
		fifo->runlist[runl].engm |= 1 << engn;
		fifo->runlist_nr = max(fifo->runlist_nr, runl + 1);
	}

	kfree(map);

	for (i = 0; i < fifo->runlist_nr; i++) {
		for (j = 0; j < ARRAY_SIZE(fifo->runlist[i].mem); j++) {
			ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST,
					      fifo->base.nr * 2/* TSG+chan */ *
					      fifo->func->runlist->size,
					      0x1000, false,
					      &fifo->runlist[i].mem[j]);
			if (ret)
				return ret;
		}

		init_waitqueue_head(&fifo->runlist[i].wait);
		INIT_LIST_HEAD(&fifo->runlist[i].cgrp);
		INIT_LIST_HEAD(&fifo->runlist[i].chan);
	}

	ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST,
			      fifo->base.nr * 0x200, 0x1000, true,
			      &fifo->user.mem);
	if (ret)
		return ret;

	ret = nvkm_vmm_get(bar, 12, nvkm_memory_size(fifo->user.mem),
			   &fifo->user.bar);
	if (ret)
		return ret;

	return nvkm_memory_map(fifo->user.mem, 0, bar, fifo->user.bar, NULL, 0);
}