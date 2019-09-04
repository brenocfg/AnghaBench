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
struct TYPE_4__ {TYPE_1__* client; } ;
struct nvkm_fifo_chan {int chid; TYPE_2__ object; } ;
struct nvkm_fifo {int dummy; } ;
struct nvkm_engine {struct nvkm_subdev subdev; } ;
struct nvkm_device {struct nvkm_fifo* fifo; } ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  g84_cipher_intr_mask ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int,char*,int,int,char*,int,int) ; 
 struct nvkm_fifo_chan* nvkm_fifo_chan_inst (struct nvkm_fifo*,int,unsigned long*) ; 
 int /*<<< orphan*/  nvkm_fifo_chan_put (struct nvkm_fifo*,unsigned long,struct nvkm_fifo_chan**) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_snprintbf (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static void
g84_cipher_intr(struct nvkm_engine *cipher)
{
	struct nvkm_subdev *subdev = &cipher->subdev;
	struct nvkm_device *device = subdev->device;
	struct nvkm_fifo *fifo = device->fifo;
	struct nvkm_fifo_chan *chan;
	u32 stat = nvkm_rd32(device, 0x102130);
	u32 mthd = nvkm_rd32(device, 0x102190);
	u32 data = nvkm_rd32(device, 0x102194);
	u32 inst = nvkm_rd32(device, 0x102188) & 0x7fffffff;
	unsigned long flags;
	char msg[128];

	chan = nvkm_fifo_chan_inst(fifo, (u64)inst << 12, &flags);
	if (stat) {
		nvkm_snprintbf(msg, sizeof(msg), g84_cipher_intr_mask, stat);
		nvkm_error(subdev,  "%08x [%s] ch %d [%010llx %s] "
				    "mthd %04x data %08x\n", stat, msg,
			   chan ? chan->chid : -1, (u64)inst << 12,
			   chan ? chan->object.client->name : "unknown",
			   mthd, data);
	}
	nvkm_fifo_chan_put(fifo, flags, &chan);

	nvkm_wr32(device, 0x102130, stat);
	nvkm_wr32(device, 0x10200c, 0x10);
}