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
struct TYPE_7__ {scalar_t__ high_speed; } ;
struct TYPE_6__ {int link; scalar_t__ proto; } ;
struct nvkm_ior {TYPE_2__ tmds; TYPE_1__ asy; TYPE_4__* disp; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_8__ {struct nvkm_device* device; } ;
struct TYPE_10__ {TYPE_3__ subdev; } ;
struct TYPE_9__ {TYPE_5__ engine; } ;

/* Variables and functions */
 scalar_t__ TMDS ; 
 int nv50_ior_base (struct nvkm_ior*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int const,int,int const) ; 

void
gf119_sor_clock(struct nvkm_ior *sor)
{
	struct nvkm_device *device = sor->disp->engine.subdev.device;
	const u32 soff = nv50_ior_base(sor);
	u32 div1 = sor->asy.link == 3;
	u32 div2 = sor->asy.link == 3;
	if (sor->asy.proto == TMDS) {
		const u32 speed = sor->tmds.high_speed ? 0x14 : 0x0a;
		nvkm_mask(device, 0x612300 + soff, 0x007c0000, speed << 18);
		if (sor->tmds.high_speed)
			div2 = 1;
	}
	nvkm_mask(device, 0x612300 + soff, 0x00000707, (div2 << 8) | div1);
}