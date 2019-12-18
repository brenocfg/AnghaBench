#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_enum {char* name; } ;
struct nvkm_engine {struct nvkm_subdev subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gk104_ce_launcherr_report ; 
 struct nvkm_enum* nvkm_enum_find (int /*<<< orphan*/ ,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int const) ; 
 int /*<<< orphan*/  nvkm_warn (struct nvkm_subdev*,char*,int,char*) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int const,int) ; 

__attribute__((used)) static void
gk104_ce_intr_launcherr(struct nvkm_engine *ce, const u32 base)
{
	struct nvkm_subdev *subdev = &ce->subdev;
	struct nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, 0x104f14 + base);
	const struct nvkm_enum *en =
		nvkm_enum_find(gk104_ce_launcherr_report, stat & 0x0000000f);
	nvkm_warn(subdev, "LAUNCHERR %08x [%s]\n", stat, en ? en->name : "");
	nvkm_wr32(device, 0x104f14 + base, 0x00000000);
}