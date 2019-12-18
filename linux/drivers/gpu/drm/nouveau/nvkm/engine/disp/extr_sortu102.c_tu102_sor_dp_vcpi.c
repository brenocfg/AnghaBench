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
typedef  int u16 ;
struct nvkm_ior {TYPE_3__* disp; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int const,int,int) ; 

__attribute__((used)) static void
tu102_sor_dp_vcpi(struct nvkm_ior *sor, int head,
		  u8 slot, u8 slot_nr, u16 pbn, u16 aligned)
{
	struct nvkm_device *device = sor->disp->engine.subdev.device;
	const u32 hoff = head * 0x800;

	nvkm_mask(device, 0x61657c + hoff, 0xffffffff, (aligned << 16) | pbn);
	nvkm_mask(device, 0x616578 + hoff, 0x00003f3f, (slot_nr << 8) | slot);
}