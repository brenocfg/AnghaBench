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
struct nvkm_device {int dummy; } ;
struct nv50_disp_chan {TYPE_4__* disp; } ;
struct TYPE_5__ {struct nvkm_device* device; } ;
struct TYPE_6__ {TYPE_1__ subdev; } ;
struct TYPE_7__ {TYPE_2__ engine; } ;
struct TYPE_8__ {TYPE_3__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  gv100_disp_core_idle (struct nv50_disp_chan*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 

__attribute__((used)) static void
gv100_disp_core_fini(struct nv50_disp_chan *chan)
{
	struct nvkm_device *device = chan->disp->base.engine.subdev.device;
	nvkm_mask(device, 0x6104e0, 0x00000010, 0x00000000);
	gv100_disp_core_idle(chan);
	nvkm_mask(device, 0x6104e0, 0x00000002, 0x00000000);
}