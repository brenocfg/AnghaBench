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
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_3__ {struct nvkm_subdev subdev; } ;
struct TYPE_4__ {TYPE_1__ engine; } ;
struct gf100_gr {TYPE_2__ base; } ;
typedef  int /*<<< orphan*/  error ;

/* Variables and functions */
 int /*<<< orphan*/  GPC_UNIT (int,int) ; 
 int /*<<< orphan*/  gf100_gpc_rop_error ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int,int,char*,int,int,int,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_snprintbf (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
gf100_gr_trap_gpc_rop(struct gf100_gr *gr, int gpc)
{
	struct nvkm_subdev *subdev = &gr->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	char error[128];
	u32 trap[4];

	trap[0] = nvkm_rd32(device, GPC_UNIT(gpc, 0x0420)) & 0x3fffffff;
	trap[1] = nvkm_rd32(device, GPC_UNIT(gpc, 0x0434));
	trap[2] = nvkm_rd32(device, GPC_UNIT(gpc, 0x0438));
	trap[3] = nvkm_rd32(device, GPC_UNIT(gpc, 0x043c));

	nvkm_snprintbf(error, sizeof(error), gf100_gpc_rop_error, trap[0]);

	nvkm_error(subdev, "GPC%d/PROP trap: %08x [%s] x = %u, y = %u, "
			   "format = %x, storage type = %x\n",
		   gpc, trap[0], error, trap[1] & 0xffff, trap[1] >> 16,
		   (trap[2] >> 8) & 0x3f, trap[3] & 0xff);
	nvkm_wr32(device, GPC_UNIT(gpc, 0x0420), 0xc0000000);
}