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
struct nvkm_fb {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ base; } ;

/* Variables and functions */
 TYPE_3__* gf100_fb (struct nvkm_fb*) ; 
 int /*<<< orphan*/  nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int /*<<< orphan*/ ) ; 

void
gp100_fb_init_unkn(struct nvkm_fb *base)
{
	struct nvkm_device *device = gf100_fb(base)->base.subdev.device;
	nvkm_wr32(device, 0x1fac80, nvkm_rd32(device, 0x100c80));
	nvkm_wr32(device, 0x1facc4, nvkm_rd32(device, 0x100cc4));
	nvkm_wr32(device, 0x1facc8, nvkm_rd32(device, 0x100cc8));
	nvkm_wr32(device, 0x1faccc, nvkm_rd32(device, 0x100ccc));
}