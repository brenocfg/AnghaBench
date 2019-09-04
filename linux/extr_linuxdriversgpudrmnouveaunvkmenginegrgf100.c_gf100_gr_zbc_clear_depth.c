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
struct nvkm_device {int dummy; } ;
struct TYPE_5__ {struct nvkm_device* device; } ;
struct TYPE_6__ {TYPE_1__ subdev; } ;
struct TYPE_7__ {TYPE_2__ engine; } ;
struct gf100_gr {TYPE_4__* zbc_depth; TYPE_3__ base; } ;
struct TYPE_8__ {int format; int ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static void
gf100_gr_zbc_clear_depth(struct gf100_gr *gr, int zbc)
{
	struct nvkm_device *device = gr->base.engine.subdev.device;
	if (gr->zbc_depth[zbc].format)
		nvkm_wr32(device, 0x405818, gr->zbc_depth[zbc].ds);
	nvkm_wr32(device, 0x40581c, gr->zbc_depth[zbc].format);
	nvkm_wr32(device, 0x405820, zbc);
	nvkm_wr32(device, 0x405824, 0x00000005); /* TRIGGER | WRITE | DEPTH */
}