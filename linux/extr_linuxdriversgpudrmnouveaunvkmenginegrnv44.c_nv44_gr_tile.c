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
struct nvkm_fb_tile {int /*<<< orphan*/  addr; int /*<<< orphan*/  limit; int /*<<< orphan*/  pitch; } ;
struct nvkm_device {int chipset; struct nvkm_fifo* fifo; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;
struct nv40_gr {TYPE_3__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV20_PGRAPH_TILE (int) ; 
 int /*<<< orphan*/  NV20_PGRAPH_TLIMIT (int) ; 
 int /*<<< orphan*/  NV20_PGRAPH_TSIZE (int) ; 
 int /*<<< orphan*/  NV40_PGRAPH_TILE1 (int) ; 
 int /*<<< orphan*/  NV40_PGRAPH_TLIMIT1 (int) ; 
 int /*<<< orphan*/  NV40_PGRAPH_TSIZE1 (int) ; 
 int /*<<< orphan*/  NV47_PGRAPH_TILE (int) ; 
 int /*<<< orphan*/  NV47_PGRAPH_TLIMIT (int) ; 
 int /*<<< orphan*/  NV47_PGRAPH_TSIZE (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  nv04_gr_idle (TYPE_3__*) ; 
 struct nv40_gr* nv40_gr (struct nvkm_gr*) ; 
 int /*<<< orphan*/  nvkm_fifo_pause (struct nvkm_fifo*,unsigned long*) ; 
 int /*<<< orphan*/  nvkm_fifo_start (struct nvkm_fifo*,unsigned long*) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nv44_gr_tile(struct nvkm_gr *base, int i, struct nvkm_fb_tile *tile)
{
	struct nv40_gr *gr = nv40_gr(base);
	struct nvkm_device *device = gr->base.engine.subdev.device;
	struct nvkm_fifo *fifo = device->fifo;
	unsigned long flags;

	nvkm_fifo_pause(fifo, &flags);
	nv04_gr_idle(&gr->base);

	switch (device->chipset) {
	case 0x44:
	case 0x4a:
		nvkm_wr32(device, NV20_PGRAPH_TSIZE(i), tile->pitch);
		nvkm_wr32(device, NV20_PGRAPH_TLIMIT(i), tile->limit);
		nvkm_wr32(device, NV20_PGRAPH_TILE(i), tile->addr);
		break;
	case 0x46:
	case 0x4c:
	case 0x63:
	case 0x67:
	case 0x68:
		nvkm_wr32(device, NV47_PGRAPH_TSIZE(i), tile->pitch);
		nvkm_wr32(device, NV47_PGRAPH_TLIMIT(i), tile->limit);
		nvkm_wr32(device, NV47_PGRAPH_TILE(i), tile->addr);
		nvkm_wr32(device, NV40_PGRAPH_TSIZE1(i), tile->pitch);
		nvkm_wr32(device, NV40_PGRAPH_TLIMIT1(i), tile->limit);
		nvkm_wr32(device, NV40_PGRAPH_TILE1(i), tile->addr);
		break;
	case 0x4e:
		nvkm_wr32(device, NV20_PGRAPH_TSIZE(i), tile->pitch);
		nvkm_wr32(device, NV20_PGRAPH_TLIMIT(i), tile->limit);
		nvkm_wr32(device, NV20_PGRAPH_TILE(i), tile->addr);
		nvkm_wr32(device, NV40_PGRAPH_TSIZE1(i), tile->pitch);
		nvkm_wr32(device, NV40_PGRAPH_TLIMIT1(i), tile->limit);
		nvkm_wr32(device, NV40_PGRAPH_TILE1(i), tile->addr);
		break;
	default:
		WARN_ON(1);
		break;
	}

	nvkm_fifo_start(fifo, &flags);
}