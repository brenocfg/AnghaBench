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
struct nvkm_enum {char* name; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_3__ {struct nvkm_subdev subdev; } ;
struct TYPE_4__ {TYPE_1__ engine; } ;
struct gf100_gr {TYPE_2__ base; } ;
typedef  int /*<<< orphan*/  glob ;

/* Variables and functions */
 int /*<<< orphan*/  TPC_UNIT (int,int,int) ; 
 int /*<<< orphan*/  gf100_mp_global_error ; 
 int /*<<< orphan*/  gf100_mp_warp_error ; 
 struct nvkm_enum* nvkm_enum_find (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int,int,int,char*,int,char*) ; 
 int nvkm_rd32 (struct nvkm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_snprintbf (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int /*<<< orphan*/ ,int) ; 

void
gf100_gr_trap_mp(struct gf100_gr *gr, int gpc, int tpc)
{
	struct nvkm_subdev *subdev = &gr->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	u32 werr = nvkm_rd32(device, TPC_UNIT(gpc, tpc, 0x648));
	u32 gerr = nvkm_rd32(device, TPC_UNIT(gpc, tpc, 0x650));
	const struct nvkm_enum *warp;
	char glob[128];

	nvkm_snprintbf(glob, sizeof(glob), gf100_mp_global_error, gerr);
	warp = nvkm_enum_find(gf100_mp_warp_error, werr & 0xffff);

	nvkm_error(subdev, "GPC%i/TPC%i/MP trap: "
			   "global %08x [%s] warp %04x [%s]\n",
		   gpc, tpc, gerr, glob, werr, warp ? warp->name : "");

	nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x648), 0x00000000);
	nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x650), gerr);
}