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
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct TYPE_8__ {TYPE_3__* client; } ;
struct nvkm_fifo_chan {int chid; TYPE_4__ object; TYPE_2__* inst; } ;
struct TYPE_5__ {struct nvkm_subdev subdev; } ;
struct nvkm_falcon {TYPE_1__ engine; } ;
struct nvkm_enum {char* name; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_7__ {char* name; } ;
struct TYPE_6__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  g98_sec_isr_error_name ; 
 struct nvkm_enum* nvkm_enum_find (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int,char*,int,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 

__attribute__((used)) static void
g98_sec_intr(struct nvkm_falcon *sec, struct nvkm_fifo_chan *chan)
{
	struct nvkm_subdev *subdev = &sec->engine.subdev;
	struct nvkm_device *device = subdev->device;
	u32 ssta = nvkm_rd32(device, 0x087040) & 0x0000ffff;
	u32 addr = nvkm_rd32(device, 0x087040) >> 16;
	u32 mthd = (addr & 0x07ff) << 2;
	u32 subc = (addr & 0x3800) >> 11;
	u32 data = nvkm_rd32(device, 0x087044);
	const struct nvkm_enum *en =
		nvkm_enum_find(g98_sec_isr_error_name, ssta);

	nvkm_error(subdev, "DISPATCH_ERROR %04x [%s] ch %d [%010llx %s] "
			   "subc %d mthd %04x data %08x\n", ssta,
		   en ? en->name : "UNKNOWN", chan ? chan->chid : -1,
		   chan ? chan->inst->addr : 0,
		   chan ? chan->object.client->name : "unknown",
		   subc, mthd, data);
}