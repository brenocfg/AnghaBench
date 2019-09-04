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
typedef  int u64 ;
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_fifo_chan {int dummy; } ;
struct TYPE_3__ {struct nvkm_subdev subdev; } ;
struct nvkm_falcon {int addr; TYPE_2__* func; TYPE_1__ engine; } ;
struct nvkm_engine {int dummy; } ;
struct nvkm_device {int /*<<< orphan*/  fifo; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* intr ) (struct nvkm_falcon*,struct nvkm_fifo_chan*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int) ; 
 struct nvkm_falcon* nvkm_falcon (struct nvkm_engine*) ; 
 struct nvkm_fifo_chan* nvkm_fifo_chan_inst (int /*<<< orphan*/ ,int,unsigned long*) ; 
 int /*<<< orphan*/  nvkm_fifo_chan_put (int /*<<< orphan*/ ,unsigned long,struct nvkm_fifo_chan**) ; 
 int nvkm_rd32 (struct nvkm_device*,int const) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int const,int) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_falcon*,struct nvkm_fifo_chan*) ; 

__attribute__((used)) static void
nvkm_falcon_intr(struct nvkm_engine *engine)
{
	struct nvkm_falcon *falcon = nvkm_falcon(engine);
	struct nvkm_subdev *subdev = &falcon->engine.subdev;
	struct nvkm_device *device = subdev->device;
	const u32 base = falcon->addr;
	u32 dest = nvkm_rd32(device, base + 0x01c);
	u32 intr = nvkm_rd32(device, base + 0x008) & dest & ~(dest >> 16);
	u32 inst = nvkm_rd32(device, base + 0x050) & 0x3fffffff;
	struct nvkm_fifo_chan *chan;
	unsigned long flags;

	chan = nvkm_fifo_chan_inst(device->fifo, (u64)inst << 12, &flags);

	if (intr & 0x00000040) {
		if (falcon->func->intr) {
			falcon->func->intr(falcon, chan);
			nvkm_wr32(device, base + 0x004, 0x00000040);
			intr &= ~0x00000040;
		}
	}

	if (intr & 0x00000010) {
		nvkm_debug(subdev, "ucode halted\n");
		nvkm_wr32(device, base + 0x004, 0x00000010);
		intr &= ~0x00000010;
	}

	if (intr)  {
		nvkm_error(subdev, "intr %08x\n", intr);
		nvkm_wr32(device, base + 0x004, intr);
	}

	nvkm_fifo_chan_put(device->fifo, flags, &chan);
}