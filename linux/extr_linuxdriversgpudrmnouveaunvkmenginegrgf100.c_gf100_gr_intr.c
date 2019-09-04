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
typedef  int u64 ;
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_gr {int dummy; } ;
struct TYPE_8__ {TYPE_3__* client; } ;
struct nvkm_fifo_chan {int chid; TYPE_4__ object; } ;
struct nvkm_enum {char* name; } ;
struct nvkm_device {scalar_t__ card_type; int /*<<< orphan*/  fifo; } ;
struct TYPE_5__ {struct nvkm_subdev subdev; } ;
struct TYPE_6__ {TYPE_1__ engine; } ;
struct gf100_gr {TYPE_2__ base; } ;
struct TYPE_7__ {char* name; } ;

/* Variables and functions */
 scalar_t__ NV_E0 ; 
 struct gf100_gr* gf100_gr (struct nvkm_gr*) ; 
 int /*<<< orphan*/  gf100_gr_ctxctl_isr (struct gf100_gr*) ; 
 int /*<<< orphan*/  gf100_gr_mthd_sw (struct nvkm_device*,int,int,int) ; 
 int /*<<< orphan*/  gf100_gr_trap_intr (struct gf100_gr*) ; 
 int /*<<< orphan*/  nv50_data_error_names ; 
 struct nvkm_enum* nvkm_enum_find (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int,...) ; 
 struct nvkm_fifo_chan* nvkm_fifo_chan_inst (int /*<<< orphan*/ ,int,unsigned long*) ; 
 int /*<<< orphan*/  nvkm_fifo_chan_put (int /*<<< orphan*/ ,unsigned long,struct nvkm_fifo_chan**) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static void
gf100_gr_intr(struct nvkm_gr *base)
{
	struct gf100_gr *gr = gf100_gr(base);
	struct nvkm_subdev *subdev = &gr->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	struct nvkm_fifo_chan *chan;
	unsigned long flags;
	u64 inst = nvkm_rd32(device, 0x409b00) & 0x0fffffff;
	u32 stat = nvkm_rd32(device, 0x400100);
	u32 addr = nvkm_rd32(device, 0x400704);
	u32 mthd = (addr & 0x00003ffc);
	u32 subc = (addr & 0x00070000) >> 16;
	u32 data = nvkm_rd32(device, 0x400708);
	u32 code = nvkm_rd32(device, 0x400110);
	u32 class;
	const char *name = "unknown";
	int chid = -1;

	chan = nvkm_fifo_chan_inst(device->fifo, (u64)inst << 12, &flags);
	if (chan) {
		name = chan->object.client->name;
		chid = chan->chid;
	}

	if (device->card_type < NV_E0 || subc < 4)
		class = nvkm_rd32(device, 0x404200 + (subc * 4));
	else
		class = 0x0000;

	if (stat & 0x00000001) {
		/*
		 * notifier interrupt, only needed for cyclestats
		 * can be safely ignored
		 */
		nvkm_wr32(device, 0x400100, 0x00000001);
		stat &= ~0x00000001;
	}

	if (stat & 0x00000010) {
		if (!gf100_gr_mthd_sw(device, class, mthd, data)) {
			nvkm_error(subdev, "ILLEGAL_MTHD ch %d [%010llx %s] "
				   "subc %d class %04x mthd %04x data %08x\n",
				   chid, inst << 12, name, subc,
				   class, mthd, data);
		}
		nvkm_wr32(device, 0x400100, 0x00000010);
		stat &= ~0x00000010;
	}

	if (stat & 0x00000020) {
		nvkm_error(subdev, "ILLEGAL_CLASS ch %d [%010llx %s] "
			   "subc %d class %04x mthd %04x data %08x\n",
			   chid, inst << 12, name, subc, class, mthd, data);
		nvkm_wr32(device, 0x400100, 0x00000020);
		stat &= ~0x00000020;
	}

	if (stat & 0x00100000) {
		const struct nvkm_enum *en =
			nvkm_enum_find(nv50_data_error_names, code);
		nvkm_error(subdev, "DATA_ERROR %08x [%s] ch %d [%010llx %s] "
				   "subc %d class %04x mthd %04x data %08x\n",
			   code, en ? en->name : "", chid, inst << 12,
			   name, subc, class, mthd, data);
		nvkm_wr32(device, 0x400100, 0x00100000);
		stat &= ~0x00100000;
	}

	if (stat & 0x00200000) {
		nvkm_error(subdev, "TRAP ch %d [%010llx %s]\n",
			   chid, inst << 12, name);
		gf100_gr_trap_intr(gr);
		nvkm_wr32(device, 0x400100, 0x00200000);
		stat &= ~0x00200000;
	}

	if (stat & 0x00080000) {
		gf100_gr_ctxctl_isr(gr);
		nvkm_wr32(device, 0x400100, 0x00080000);
		stat &= ~0x00080000;
	}

	if (stat) {
		nvkm_error(subdev, "intr %08x\n", stat);
		nvkm_wr32(device, 0x400100, stat);
	}

	nvkm_wr32(device, 0x400500, 0x00010001);
	nvkm_fifo_chan_put(device->fifo, flags, &chan);
}