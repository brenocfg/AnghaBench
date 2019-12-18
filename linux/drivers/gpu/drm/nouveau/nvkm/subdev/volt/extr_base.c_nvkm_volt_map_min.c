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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct nvkm_volt {TYPE_2__ subdev; } ;
struct nvkm_bios {int dummy; } ;
struct nvbios_vmap_entry {int link; int min; } ;
struct TYPE_3__ {struct nvkm_bios* bios; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ nvbios_vmap_entry_parse (struct nvkm_bios*,int,int*,int*,struct nvbios_vmap_entry*) ; 

int
nvkm_volt_map_min(struct nvkm_volt *volt, u8 id)
{
	struct nvkm_bios *bios = volt->subdev.device->bios;
	struct nvbios_vmap_entry info;
	u8  ver, len;
	u32 vmap;

	vmap = nvbios_vmap_entry_parse(bios, id, &ver, &len, &info);
	if (vmap) {
		if (info.link != 0xff) {
			int ret = nvkm_volt_map_min(volt, info.link);
			if (ret < 0)
				return ret;
			info.min += ret;
		}
		return info.min;
	}

	return id ? id * 10000 : -ENODEV;
}