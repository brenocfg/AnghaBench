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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_gr {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_7__ {TYPE_2__* engine; } ;
struct nv10_gr_chan {TYPE_4__* gr; TYPE_3__ object; } ;
struct TYPE_8__ {struct nvkm_gr base; } ;
struct TYPE_5__ {struct nvkm_device* device; } ;
struct TYPE_6__ {TYPE_1__ subdev; } ;

/* Variables and functions */
 int NV10_PGRAPH_DEBUG_4 ; 
 int /*<<< orphan*/  nv04_gr_idle (struct nvkm_gr*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 

__attribute__((used)) static void
nv17_gr_mthd_lma_enable(struct nv10_gr_chan *chan, u32 mthd, u32 data)
{
	struct nvkm_device *device = chan->object.engine->subdev.device;
	struct nvkm_gr *gr = &chan->gr->base;

	nv04_gr_idle(gr);

	nvkm_mask(device, NV10_PGRAPH_DEBUG_4, 0x00000100, 0x00000100);
	nvkm_mask(device, 0x4006b0, 0x08000000, 0x08000000);
}