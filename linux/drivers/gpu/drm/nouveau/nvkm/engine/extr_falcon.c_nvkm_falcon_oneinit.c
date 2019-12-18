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
struct nvkm_subdev {struct nvkm_device* device; } ;
struct TYPE_6__ {int limit; } ;
struct TYPE_5__ {int limit; } ;
struct TYPE_4__ {struct nvkm_subdev subdev; } ;
struct nvkm_falcon {int addr; int version; int secret; TYPE_3__ data; TYPE_2__ code; TYPE_1__ engine; } ;
struct nvkm_engine {int dummy; } ;
struct nvkm_device {int chipset; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*,int) ; 
 struct nvkm_falcon* nvkm_falcon (struct nvkm_engine*) ; 
 int nvkm_rd32 (struct nvkm_device*,int const) ; 

__attribute__((used)) static int
nvkm_falcon_oneinit(struct nvkm_engine *engine)
{
	struct nvkm_falcon *falcon = nvkm_falcon(engine);
	struct nvkm_subdev *subdev = &falcon->engine.subdev;
	struct nvkm_device *device = subdev->device;
	const u32 base = falcon->addr;
	u32 caps;

	/* determine falcon capabilities */
	if (device->chipset <  0xa3 ||
	    device->chipset == 0xaa || device->chipset == 0xac) {
		falcon->version = 0;
		falcon->secret  = (falcon->addr == 0x087000) ? 1 : 0;
	} else {
		caps = nvkm_rd32(device, base + 0x12c);
		falcon->version = (caps & 0x0000000f);
		falcon->secret  = (caps & 0x00000030) >> 4;
	}

	caps = nvkm_rd32(device, base + 0x108);
	falcon->code.limit = (caps & 0x000001ff) << 8;
	falcon->data.limit = (caps & 0x0003fe00) >> 1;

	nvkm_debug(subdev, "falcon version: %d\n", falcon->version);
	nvkm_debug(subdev, "secret level: %d\n", falcon->secret);
	nvkm_debug(subdev, "code limit: %d\n", falcon->code.limit);
	nvkm_debug(subdev, "data limit: %d\n", falcon->data.limit);
	return 0;
}