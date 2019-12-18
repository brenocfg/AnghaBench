#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_engine {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  lock; struct nvkm_subdev subdev; } ;
struct nv31_mpeg {TYPE_5__ engine; TYPE_4__* chan; } ;
struct TYPE_8__ {TYPE_2__* client; } ;
struct TYPE_9__ {TYPE_3__ object; TYPE_1__* fifo; } ;
struct TYPE_7__ {char* name; } ;
struct TYPE_6__ {int chid; } ;

/* Variables and functions */
 struct nv31_mpeg* nv31_mpeg (struct nvkm_engine*) ; 
 scalar_t__ nv31_mpeg_mthd (struct nv31_mpeg*,int,int) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int,char*,int,int,int,int) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
nv31_mpeg_intr(struct nvkm_engine *engine)
{
	struct nv31_mpeg *mpeg = nv31_mpeg(engine);
	struct nvkm_subdev *subdev = &mpeg->engine.subdev;
	struct nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, 0x00b100);
	u32 type = nvkm_rd32(device, 0x00b230);
	u32 mthd = nvkm_rd32(device, 0x00b234);
	u32 data = nvkm_rd32(device, 0x00b238);
	u32 show = stat;
	unsigned long flags;

	spin_lock_irqsave(&mpeg->engine.lock, flags);

	if (stat & 0x01000000) {
		/* happens on initial binding of the object */
		if (type == 0x00000020 && mthd == 0x0000) {
			nvkm_mask(device, 0x00b308, 0x00000000, 0x00000000);
			show &= ~0x01000000;
		}

		if (type == 0x00000010) {
			if (nv31_mpeg_mthd(mpeg, mthd, data))
				show &= ~0x01000000;
		}
	}

	nvkm_wr32(device, 0x00b100, stat);
	nvkm_wr32(device, 0x00b230, 0x00000001);

	if (show) {
		nvkm_error(subdev, "ch %d [%s] %08x %08x %08x %08x\n",
			   mpeg->chan ? mpeg->chan->fifo->chid : -1,
			   mpeg->chan ? mpeg->chan->object.client->name :
			   "unknown", stat, type, mthd, data);
	}

	spin_unlock_irqrestore(&mpeg->engine.lock, flags);
}