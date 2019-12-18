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
struct nvkm_fb {TYPE_3__* func; } ;
struct nvkm_device {int /*<<< orphan*/  therm; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct gf100_fb {int r100c10; scalar_t__ r100c10_page; TYPE_2__ base; } ;
struct TYPE_6__ {int /*<<< orphan*/  clkgate_pack; } ;

/* Variables and functions */
 struct gf100_fb* gf100_fb (struct nvkm_fb*) ; 
 int /*<<< orphan*/  nvkm_therm_clkgate_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

void
gf100_fb_init(struct nvkm_fb *base)
{
	struct gf100_fb *fb = gf100_fb(base);
	struct nvkm_device *device = fb->base.subdev.device;

	if (fb->r100c10_page)
		nvkm_wr32(device, 0x100c10, fb->r100c10 >> 8);

	if (base->func->clkgate_pack) {
		nvkm_therm_clkgate_init(device->therm,
					base->func->clkgate_pack);
	}
}