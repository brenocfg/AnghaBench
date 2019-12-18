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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct nvkm_bios {int dummy; } ;
struct nvbios_boostS {int min; int max; void* percent; void* domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct nvbios_boostS*,int,int) ; 
 scalar_t__ nvbios_boostSe (struct nvkm_bios*,int,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 
 int nvbios_rd16 (struct nvkm_bios*,scalar_t__) ; 

u32
nvbios_boostSp(struct nvkm_bios *bios, int idx,
	       u32 data, u8 *ver, u8 *hdr, u8 cnt, u8 len,
	       struct nvbios_boostS *info)
{
	data = nvbios_boostSe(bios, idx, data, ver, hdr, cnt, len);
	memset(info, 0x00, sizeof(*info));
	if (data) {
		info->domain  = nvbios_rd08(bios, data + 0x00);
		info->percent = nvbios_rd08(bios, data + 0x01);
		info->min     = nvbios_rd16(bios, data + 0x02) * 1000;
		info->max     = nvbios_rd16(bios, data + 0x04) * 1000;
	}
	return data;
}