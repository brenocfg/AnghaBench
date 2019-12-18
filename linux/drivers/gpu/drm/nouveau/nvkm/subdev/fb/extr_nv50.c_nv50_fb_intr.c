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
typedef  int u8 ;
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct TYPE_6__ {TYPE_2__* client; } ;
struct nvkm_fifo_chan {int chid; TYPE_3__ object; } ;
struct nvkm_fifo {int dummy; } ;
struct nvkm_fb {int dummy; } ;
struct nvkm_enum {char* name; scalar_t__ data; } ;
struct nvkm_device {int chipset; struct nvkm_fifo* fifo; } ;
struct TYPE_4__ {struct nvkm_subdev subdev; } ;
struct nv50_fb {TYPE_1__ base; } ;
struct TYPE_5__ {char* name; } ;

/* Variables and functions */
 struct nv50_fb* nv50_fb (struct nvkm_fb*) ; 
 struct nvkm_enum* nvkm_enum_find (scalar_t__,int) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,char*,int,int,int,int,int,char*,int,char*,int,char*,int,char*,int,char*) ; 
 struct nvkm_fifo_chan* nvkm_fifo_chan_inst (struct nvkm_fifo*,int,unsigned long*) ; 
 int /*<<< orphan*/  nvkm_fifo_chan_put (struct nvkm_fifo*,unsigned long,struct nvkm_fifo_chan**) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 
 scalar_t__ vm_client ; 
 scalar_t__ vm_engine ; 
 scalar_t__ vm_fault ; 

__attribute__((used)) static void
nv50_fb_intr(struct nvkm_fb *base)
{
	struct nv50_fb *fb = nv50_fb(base);
	struct nvkm_subdev *subdev = &fb->base.subdev;
	struct nvkm_device *device = subdev->device;
	struct nvkm_fifo *fifo = device->fifo;
	struct nvkm_fifo_chan *chan;
	const struct nvkm_enum *en, *re, *cl, *sc;
	u32 trap[6], idx, inst;
	u8 st0, st1, st2, st3;
	unsigned long flags;
	int i;

	idx = nvkm_rd32(device, 0x100c90);
	if (!(idx & 0x80000000))
		return;
	idx &= 0x00ffffff;

	for (i = 0; i < 6; i++) {
		nvkm_wr32(device, 0x100c90, idx | i << 24);
		trap[i] = nvkm_rd32(device, 0x100c94);
	}
	nvkm_wr32(device, 0x100c90, idx | 0x80000000);

	/* decode status bits into something more useful */
	if (device->chipset  < 0xa3 ||
	    device->chipset == 0xaa || device->chipset == 0xac) {
		st0 = (trap[0] & 0x0000000f) >> 0;
		st1 = (trap[0] & 0x000000f0) >> 4;
		st2 = (trap[0] & 0x00000f00) >> 8;
		st3 = (trap[0] & 0x0000f000) >> 12;
	} else {
		st0 = (trap[0] & 0x000000ff) >> 0;
		st1 = (trap[0] & 0x0000ff00) >> 8;
		st2 = (trap[0] & 0x00ff0000) >> 16;
		st3 = (trap[0] & 0xff000000) >> 24;
	}
	inst = ((trap[2] << 16) | trap[1]) << 12;

	en = nvkm_enum_find(vm_engine, st0);
	re = nvkm_enum_find(vm_fault , st1);
	cl = nvkm_enum_find(vm_client, st2);
	if      (cl && cl->data) sc = nvkm_enum_find(cl->data, st3);
	else if (en && en->data) sc = nvkm_enum_find(en->data, st3);
	else                     sc = NULL;

	chan = nvkm_fifo_chan_inst(fifo, inst, &flags);
	nvkm_error(subdev, "trapped %s at %02x%04x%04x on channel %d [%08x %s] "
			   "engine %02x [%s] client %02x [%s] "
			   "subclient %02x [%s] reason %08x [%s]\n",
		   (trap[5] & 0x00000100) ? "read" : "write",
		   trap[5] & 0xff, trap[4] & 0xffff, trap[3] & 0xffff,
		   chan ? chan->chid : -1, inst,
		   chan ? chan->object.client->name : "unknown",
		   st0, en ? en->name : "",
		   st2, cl ? cl->name : "", st3, sc ? sc->name : "",
		   st1, re ? re->name : "");
	nvkm_fifo_chan_put(fifo, flags, &chan);
}