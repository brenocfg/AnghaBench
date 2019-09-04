#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nvkm_sw_chan {int dummy; } ;
struct TYPE_12__ {struct nvkm_device* device; } ;
struct nvkm_engine {TYPE_6__ subdev; } ;
struct nvkm_device {TYPE_2__* disp; } ;
struct TYPE_9__ {int ctxdma; int offset; int value; int /*<<< orphan*/ * notify; } ;
struct TYPE_10__ {struct nvkm_engine* engine; } ;
struct TYPE_11__ {TYPE_4__ object; } ;
struct nv50_sw_chan {TYPE_3__ vblank; TYPE_5__ base; } ;
struct TYPE_7__ {int index_nr; } ;
struct TYPE_8__ {TYPE_1__ vblank; } ;

/* Variables and functions */
 struct nv50_sw_chan* nv50_sw_chan (struct nvkm_sw_chan*) ; 
 int /*<<< orphan*/  nvkm_notify_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
nv50_sw_chan_mthd(struct nvkm_sw_chan *base, int subc, u32 mthd, u32 data)
{
	struct nv50_sw_chan *chan = nv50_sw_chan(base);
	struct nvkm_engine *engine = chan->base.object.engine;
	struct nvkm_device *device = engine->subdev.device;
	switch (mthd) {
	case 0x018c: chan->vblank.ctxdma = data; return true;
	case 0x0400: chan->vblank.offset = data; return true;
	case 0x0404: chan->vblank.value  = data; return true;
	case 0x0408:
		if (data < device->disp->vblank.index_nr) {
			nvkm_notify_get(&chan->vblank.notify[data]);
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}