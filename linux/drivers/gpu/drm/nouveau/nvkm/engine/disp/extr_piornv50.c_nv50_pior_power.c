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
typedef  int u32 ;
struct nvkm_ior {TYPE_3__* disp; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;

/* Variables and functions */
 int nv50_ior_base (struct nvkm_ior*) ; 
 int /*<<< orphan*/  nv50_pior_power_wait (struct nvkm_device*,int const) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int const,int const,int const) ; 

__attribute__((used)) static void
nv50_pior_power(struct nvkm_ior *pior, bool normal, bool pu,
	       bool data, bool vsync, bool hsync)
{
	struct nvkm_device *device = pior->disp->engine.subdev.device;
	const u32  poff = nv50_ior_base(pior);
	const u32 shift = normal ? 0 : 16;
	const u32 state = 0x80000000 | (0x00000001 * !!pu) << shift;
	const u32 field = 0x80000000 | (0x00000101 << shift);

	nv50_pior_power_wait(device, poff);
	nvkm_mask(device, 0x61e004 + poff, field, state);
	nv50_pior_power_wait(device, poff);
}