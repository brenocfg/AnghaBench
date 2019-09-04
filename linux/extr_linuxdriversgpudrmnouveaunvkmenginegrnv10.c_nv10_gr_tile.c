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
struct nvkm_gr {int dummy; } ;
struct nvkm_fifo {int dummy; } ;
struct nvkm_fb_tile {int /*<<< orphan*/  addr; int /*<<< orphan*/  pitch; int /*<<< orphan*/  limit; } ;
struct nvkm_device {struct nvkm_fifo* fifo; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;
struct nv10_gr {TYPE_3__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV10_PGRAPH_TILE (int) ; 
 int /*<<< orphan*/  NV10_PGRAPH_TLIMIT (int) ; 
 int /*<<< orphan*/  NV10_PGRAPH_TSIZE (int) ; 
 int /*<<< orphan*/  nv04_gr_idle (TYPE_3__*) ; 
 struct nv10_gr* nv10_gr (struct nvkm_gr*) ; 
 int /*<<< orphan*/  nvkm_fifo_pause (struct nvkm_fifo*,unsigned long*) ; 
 int /*<<< orphan*/  nvkm_fifo_start (struct nvkm_fifo*,unsigned long*) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
nv10_gr_tile(struct nvkm_gr *base, int i, struct nvkm_fb_tile *tile)
{
	struct nv10_gr *gr = nv10_gr(base);
	struct nvkm_device *device = gr->base.engine.subdev.device;
	struct nvkm_fifo *fifo = device->fifo;
	unsigned long flags;

	nvkm_fifo_pause(fifo, &flags);
	nv04_gr_idle(&gr->base);

	nvkm_wr32(device, NV10_PGRAPH_TLIMIT(i), tile->limit);
	nvkm_wr32(device, NV10_PGRAPH_TSIZE(i), tile->pitch);
	nvkm_wr32(device, NV10_PGRAPH_TILE(i), tile->addr);

	nvkm_fifo_start(fifo, &flags);
}