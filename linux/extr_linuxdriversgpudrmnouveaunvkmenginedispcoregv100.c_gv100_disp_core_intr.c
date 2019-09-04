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
struct nvkm_device {int dummy; } ;
struct nv50_disp_chan {TYPE_4__* disp; } ;
struct TYPE_5__ {struct nvkm_device* device; } ;
struct TYPE_6__ {TYPE_1__ subdev; } ;
struct TYPE_7__ {TYPE_2__ engine; } ;
struct TYPE_8__ {TYPE_3__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int const,int const) ; 

__attribute__((used)) static void
gv100_disp_core_intr(struct nv50_disp_chan *chan, bool en)
{
	struct nvkm_device *device = chan->disp->base.engine.subdev.device;
	const u32 mask = 0x00000001;
	const u32 data = en ? mask : 0;
	nvkm_mask(device, 0x611dac, mask, data);
}