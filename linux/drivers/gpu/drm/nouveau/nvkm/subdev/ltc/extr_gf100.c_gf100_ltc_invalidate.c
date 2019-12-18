#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_ltc {TYPE_1__ subdev; } ;
struct nvkm_device {int dummy; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_debug (TYPE_1__*,char*,scalar_t__) ; 
 scalar_t__ nvkm_wait_msec (struct nvkm_device*,int,int,int,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

void
gf100_ltc_invalidate(struct nvkm_ltc *ltc)
{
	struct nvkm_device *device = ltc->subdev.device;
	s64 taken;

	nvkm_wr32(device, 0x70004, 0x00000001);
	taken = nvkm_wait_msec(device, 2000, 0x70004, 0x00000003, 0x00000000);

	if (taken > 0)
		nvkm_debug(&ltc->subdev, "LTC invalidate took %lld ns\n", taken);
}