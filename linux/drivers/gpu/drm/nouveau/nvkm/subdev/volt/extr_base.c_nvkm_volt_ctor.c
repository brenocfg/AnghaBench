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
typedef  int /*<<< orphan*/  u8 ;
struct nvkm_volt_func {int dummy; } ;
struct nvkm_volt {int max0_id; int max1_id; int max2_id; int vid_nr; TYPE_1__* vid; int /*<<< orphan*/  subdev; int /*<<< orphan*/  max_uv; int /*<<< orphan*/  min_uv; struct nvkm_volt_func const* func; } ;
struct nvkm_device {struct nvkm_bios* bios; } ;
struct nvkm_bios {int dummy; } ;
struct nvbios_vmap {int max0; int max1; int max2; } ;
struct TYPE_2__ {int /*<<< orphan*/  uv; int /*<<< orphan*/  vid; } ;

/* Variables and functions */
 scalar_t__ nvbios_vmap_parse (struct nvkm_bios*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nvbios_vmap*) ; 
 int /*<<< orphan*/  nvkm_debug (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_subdev_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_volt ; 
 int /*<<< orphan*/  nvkm_volt_parse_bios (struct nvkm_bios*,struct nvkm_volt*) ; 

void
nvkm_volt_ctor(const struct nvkm_volt_func *func, struct nvkm_device *device,
	       int index, struct nvkm_volt *volt)
{
	struct nvkm_bios *bios = device->bios;
	int i;

	nvkm_subdev_ctor(&nvkm_volt, device, index, &volt->subdev);
	volt->func = func;

	/* Assuming the non-bios device should build the voltage table later */
	if (bios) {
		u8 ver, hdr, cnt, len;
		struct nvbios_vmap vmap;

		nvkm_volt_parse_bios(bios, volt);
		nvkm_debug(&volt->subdev, "min: %iuv max: %iuv\n",
			   volt->min_uv, volt->max_uv);

		if (nvbios_vmap_parse(bios, &ver, &hdr, &cnt, &len, &vmap)) {
			volt->max0_id = vmap.max0;
			volt->max1_id = vmap.max1;
			volt->max2_id = vmap.max2;
		} else {
			volt->max0_id = 0xff;
			volt->max1_id = 0xff;
			volt->max2_id = 0xff;
		}
	}

	if (volt->vid_nr) {
		for (i = 0; i < volt->vid_nr; i++) {
			nvkm_debug(&volt->subdev, "VID %02x: %duv\n",
				   volt->vid[i].vid, volt->vid[i].uv);
		}
	}
}