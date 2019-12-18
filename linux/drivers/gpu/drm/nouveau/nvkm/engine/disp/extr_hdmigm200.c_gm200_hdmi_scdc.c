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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_8__ {int high_speed; } ;
struct nvkm_ior {TYPE_4__ tmds; TYPE_3__* disp; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_5__ {struct nvkm_device* device; } ;
struct TYPE_6__ {TYPE_1__ subdev; } ;
struct TYPE_7__ {TYPE_2__ engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int const,int,int const) ; 

void
gm200_hdmi_scdc(struct nvkm_ior *ior, int head, u8 scdc)
{
	struct nvkm_device *device = ior->disp->engine.subdev.device;
	const u32 hoff = head * 0x800;
	const u32 ctrl = scdc & 0x3;

	nvkm_mask(device, 0x61c5bc + hoff, 0x00000003, ctrl);

	ior->tmds.high_speed = !!(scdc & 0x2);
}