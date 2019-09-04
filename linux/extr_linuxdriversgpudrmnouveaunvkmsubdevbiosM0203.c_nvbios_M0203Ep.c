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
typedef  int u8 ;
typedef  int u32 ;
struct nvkm_bios {int dummy; } ;
struct nvbios_M0203E {int type; int strap; int group; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct nvbios_M0203E*,int,int) ; 
 int nvbios_M0203Ee (struct nvkm_bios*,int,int*,int*) ; 
 int nvbios_rd08 (struct nvkm_bios*,int) ; 

u32
nvbios_M0203Ep(struct nvkm_bios *bios, int idx, u8 *ver, u8 *hdr,
	       struct nvbios_M0203E *info)
{
	u32 data = nvbios_M0203Ee(bios, idx, ver, hdr);
	memset(info, 0x00, sizeof(*info));
	switch (!!data * *ver) {
	case 0x10:
		info->type  = (nvbios_rd08(bios, data + 0x00) & 0x0f) >> 0;
		info->strap = (nvbios_rd08(bios, data + 0x00) & 0xf0) >> 4;
		info->group = (nvbios_rd08(bios, data + 0x01) & 0x0f) >> 0;
		return data;
	default:
		break;
	}
	return 0x00000000;
}