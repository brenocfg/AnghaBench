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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_device {int dummy; } ;
struct gf100_grctx {TYPE_4__* gr; } ;
struct TYPE_5__ {struct nvkm_device* device; } ;
struct TYPE_6__ {TYPE_1__ subdev; } ;
struct TYPE_7__ {TYPE_2__ engine; } ;
struct TYPE_8__ {TYPE_3__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmio_wr32 (struct gf100_grctx*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_rd32 (struct nvkm_device*,int) ; 

void
gk104_grctx_generate_patch_ltc(struct gf100_grctx *info)
{
	struct nvkm_device *device = info->gr->base.engine.subdev.device;
	u32 data0 = nvkm_rd32(device, 0x17e91c);
	u32 data1 = nvkm_rd32(device, 0x17e920);
	/*XXX: Figure out how to modify this correctly! */
	mmio_wr32(info, 0x17e91c, data0);
	mmio_wr32(info, 0x17e920, data1);
}