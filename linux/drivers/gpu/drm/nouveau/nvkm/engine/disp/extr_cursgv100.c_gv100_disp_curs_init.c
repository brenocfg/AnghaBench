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
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_8__ {int ctrl; } ;
struct nv50_disp_chan {TYPE_4__ chid; TYPE_3__* disp; } ;
struct TYPE_5__ {struct nvkm_subdev subdev; } ;
struct TYPE_6__ {TYPE_1__ engine; } ;
struct TYPE_7__ {TYPE_2__ base; } ;

/* Variables and functions */
 int gv100_disp_curs_idle (struct nv50_disp_chan*) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static int
gv100_disp_curs_init(struct nv50_disp_chan *chan)
{
	struct nvkm_subdev *subdev = &chan->disp->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	nvkm_wr32(device, 0x6104e0 + chan->chid.ctrl * 4, 0x00000001);
	return gv100_disp_curs_idle(chan);
}