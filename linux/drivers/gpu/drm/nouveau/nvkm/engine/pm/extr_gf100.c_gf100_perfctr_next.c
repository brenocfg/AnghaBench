#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct nvkm_device* device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;
struct nvkm_pm {TYPE_2__ engine; } ;
struct nvkm_perfdom {int signal_nr; scalar_t__ addr; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,scalar_t__,int) ; 

__attribute__((used)) static void
gf100_perfctr_next(struct nvkm_pm *pm, struct nvkm_perfdom *dom)
{
	struct nvkm_device *device = pm->engine.subdev.device;
	nvkm_wr32(device, dom->addr + 0x06c, dom->signal_nr - 0x40 + 0x27);
	nvkm_wr32(device, dom->addr + 0x0ec, 0x00000011);
}