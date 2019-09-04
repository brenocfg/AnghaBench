#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct TYPE_8__ {TYPE_2__* client; } ;
struct nvkm_fifo_chan {int chid; TYPE_3__ object; } ;
struct nvkm_enum {int data2; char* name; } ;
struct nvkm_engine {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_6__ {struct nvkm_subdev subdev; } ;
struct TYPE_9__ {TYPE_1__ engine; } ;
struct gf100_fifo {TYPE_4__ base; } ;
typedef  int /*<<< orphan*/  gpcid ;
struct TYPE_7__ {char* name; } ;

/* Variables and functions */
#define  NVKM_ENGINE_IFB 130 
#define  NVKM_SUBDEV_BAR 129 
#define  NVKM_SUBDEV_INSTMEM 128 
 int /*<<< orphan*/  gf100_fifo_fault_engine ; 
 int /*<<< orphan*/  gf100_fifo_fault_gpcclient ; 
 int /*<<< orphan*/  gf100_fifo_fault_hubclient ; 
 int /*<<< orphan*/  gf100_fifo_fault_reason ; 
 int /*<<< orphan*/  gf100_fifo_recover (struct gf100_fifo*,struct nvkm_engine*,void*) ; 
 struct nvkm_engine* nvkm_device_engine (struct nvkm_device*,int) ; 
 struct nvkm_enum* nvkm_enum_find (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,char*,int,int,char*,int,char*,char*,int,char*,int,int,char*) ; 
 struct nvkm_fifo_chan* nvkm_fifo_chan_inst (TYPE_4__*,int,unsigned long*) ; 
 int /*<<< orphan*/  nvkm_fifo_chan_put (TYPE_4__*,unsigned long,struct nvkm_fifo_chan**) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
gf100_fifo_intr_fault(struct gf100_fifo *fifo, int unit)
{
	struct nvkm_subdev *subdev = &fifo->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	u32 inst = nvkm_rd32(device, 0x002800 + (unit * 0x10));
	u32 valo = nvkm_rd32(device, 0x002804 + (unit * 0x10));
	u32 vahi = nvkm_rd32(device, 0x002808 + (unit * 0x10));
	u32 stat = nvkm_rd32(device, 0x00280c + (unit * 0x10));
	u32 gpc    = (stat & 0x1f000000) >> 24;
	u32 client = (stat & 0x00001f00) >> 8;
	u32 write  = (stat & 0x00000080);
	u32 hub    = (stat & 0x00000040);
	u32 reason = (stat & 0x0000000f);
	const struct nvkm_enum *er, *eu, *ec;
	struct nvkm_engine *engine = NULL;
	struct nvkm_fifo_chan *chan;
	unsigned long flags;
	char gpcid[8] = "";

	er = nvkm_enum_find(gf100_fifo_fault_reason, reason);
	eu = nvkm_enum_find(gf100_fifo_fault_engine, unit);
	if (hub) {
		ec = nvkm_enum_find(gf100_fifo_fault_hubclient, client);
	} else {
		ec = nvkm_enum_find(gf100_fifo_fault_gpcclient, client);
		snprintf(gpcid, sizeof(gpcid), "GPC%d/", gpc);
	}

	if (eu && eu->data2) {
		switch (eu->data2) {
		case NVKM_SUBDEV_BAR:
			nvkm_mask(device, 0x001704, 0x00000000, 0x00000000);
			break;
		case NVKM_SUBDEV_INSTMEM:
			nvkm_mask(device, 0x001714, 0x00000000, 0x00000000);
			break;
		case NVKM_ENGINE_IFB:
			nvkm_mask(device, 0x001718, 0x00000000, 0x00000000);
			break;
		default:
			engine = nvkm_device_engine(device, eu->data2);
			break;
		}
	}

	chan = nvkm_fifo_chan_inst(&fifo->base, (u64)inst << 12, &flags);

	nvkm_error(subdev,
		   "%s fault at %010llx engine %02x [%s] client %02x [%s%s] "
		   "reason %02x [%s] on channel %d [%010llx %s]\n",
		   write ? "write" : "read", (u64)vahi << 32 | valo,
		   unit, eu ? eu->name : "", client, gpcid, ec ? ec->name : "",
		   reason, er ? er->name : "", chan ? chan->chid : -1,
		   (u64)inst << 12,
		   chan ? chan->object.client->name : "unknown");

	if (engine && chan)
		gf100_fifo_recover(fifo, engine, (void *)chan);
	nvkm_fifo_chan_put(&fifo->base, flags, &chan);
}