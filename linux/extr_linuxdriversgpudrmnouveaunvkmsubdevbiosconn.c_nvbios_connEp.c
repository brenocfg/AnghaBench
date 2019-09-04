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
struct nvbios_connE {int type; int location; int hpd; int dp; int di; int sr; int lcdid; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct nvbios_connE*,int,int) ; 
 int nvbios_connEe (struct nvkm_bios*,int,int*,int*) ; 
 int nvbios_rd08 (struct nvkm_bios*,int) ; 

u32
nvbios_connEp(struct nvkm_bios *bios, u8 idx, u8 *ver, u8 *len,
	      struct nvbios_connE *info)
{
	u32 data = nvbios_connEe(bios, idx, ver, len);
	memset(info, 0x00, sizeof(*info));
	switch (!!data * *ver) {
	case 0x30:
	case 0x40:
		info->type     =  nvbios_rd08(bios, data + 0x00);
		info->location =  nvbios_rd08(bios, data + 0x01) & 0x0f;
		info->hpd      = (nvbios_rd08(bios, data + 0x01) & 0x30) >> 4;
		info->dp       = (nvbios_rd08(bios, data + 0x01) & 0xc0) >> 6;
		if (*len < 4)
			return data;
		info->hpd     |= (nvbios_rd08(bios, data + 0x02) & 0x03) << 2;
		info->dp      |=  nvbios_rd08(bios, data + 0x02) & 0x0c;
		info->di       = (nvbios_rd08(bios, data + 0x02) & 0xf0) >> 4;
		info->hpd     |= (nvbios_rd08(bios, data + 0x03) & 0x07) << 4;
		info->sr       = (nvbios_rd08(bios, data + 0x03) & 0x08) >> 3;
		info->lcdid    = (nvbios_rd08(bios, data + 0x03) & 0x70) >> 4;
		return data;
	default:
		break;
	}
	return 0x00000000;
}