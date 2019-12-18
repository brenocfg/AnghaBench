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
struct nvkm_volt {int speedo; TYPE_2__ subdev; } ;
struct nvkm_bios {int dummy; } ;
struct nvbios_vmap_entry {int mode; int min; int max; int link; scalar_t__* arg; } ;
typedef  int s64 ;
struct TYPE_3__ {struct nvkm_bios* bios; } ;

/* Variables and functions */
 int ENODEV ; 
 int div64_s64 (int,int) ; 
 int /*<<< orphan*/  max (int,int) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 scalar_t__ nvbios_vmap_entry_parse (struct nvkm_bios*,int,int*,int*,struct nvbios_vmap_entry*) ; 

int
nvkm_volt_map(struct nvkm_volt *volt, u8 id, u8 temp)
{
	struct nvkm_bios *bios = volt->subdev.device->bios;
	struct nvbios_vmap_entry info;
	u8  ver, len;
	u32 vmap;

	vmap = nvbios_vmap_entry_parse(bios, id, &ver, &len, &info);
	if (vmap) {
		s64 result;

		if (volt->speedo < 0)
			return volt->speedo;

		if (ver == 0x10 || (ver == 0x20 && info.mode == 0)) {
			result  = div64_s64((s64)info.arg[0], 10);
			result += div64_s64((s64)info.arg[1] * volt->speedo, 10);
			result += div64_s64((s64)info.arg[2] * volt->speedo * volt->speedo, 100000);
		} else if (ver == 0x20) {
			switch (info.mode) {
			/* 0x0 handled above! */
			case 0x1:
				result =  ((s64)info.arg[0] * 15625) >> 18;
				result += ((s64)info.arg[1] * volt->speedo * 15625) >> 18;
				result += ((s64)info.arg[2] * temp * 15625) >> 10;
				result += ((s64)info.arg[3] * volt->speedo * temp * 15625) >> 18;
				result += ((s64)info.arg[4] * volt->speedo * volt->speedo * 15625) >> 30;
				result += ((s64)info.arg[5] * temp * temp * 15625) >> 18;
				break;
			case 0x3:
				result = (info.min + info.max) / 2;
				break;
			case 0x2:
			default:
				result = info.min;
				break;
			}
		} else {
			return -ENODEV;
		}

		result = min(max(result, (s64)info.min), (s64)info.max);

		if (info.link != 0xff) {
			int ret = nvkm_volt_map(volt, info.link, temp);
			if (ret < 0)
				return ret;
			result += ret;
		}
		return result;
	}

	return id ? id * 10000 : -ENODEV;
}