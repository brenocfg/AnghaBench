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
typedef  int u16 ;
struct nvkm_bios {int dummy; } ;
struct nvbios_dpout {int mask; void** script; void* lnkcmp; void* flags; void* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct nvbios_dpout*,int,int) ; 
 int nvbios_dpout_entry (struct nvkm_bios*,int,int*,int*,int*,int*) ; 
 void* nvbios_rd08 (struct nvkm_bios*,int) ; 
 void* nvbios_rd16 (struct nvkm_bios*,int) ; 

u16
nvbios_dpout_parse(struct nvkm_bios *bios, u8 idx,
		   u8 *ver, u8 *hdr, u8 *cnt, u8 *len,
		   struct nvbios_dpout *info)
{
	u16 data = nvbios_dpout_entry(bios, idx, ver, hdr, cnt, len);
	memset(info, 0x00, sizeof(*info));
	if (data && *ver) {
		info->type = nvbios_rd16(bios, data + 0x00);
		info->mask = nvbios_rd16(bios, data + 0x02);
		switch (*ver) {
		case 0x20:
			info->mask |= 0x00c0; /* match any link */
			/* fall-through */
		case 0x21:
		case 0x30:
			info->flags     = nvbios_rd08(bios, data + 0x05);
			info->script[0] = nvbios_rd16(bios, data + 0x06);
			info->script[1] = nvbios_rd16(bios, data + 0x08);
			if (*len >= 0x0c)
				info->lnkcmp    = nvbios_rd16(bios, data + 0x0a);
			if (*len >= 0x0f) {
				info->script[2] = nvbios_rd16(bios, data + 0x0c);
				info->script[3] = nvbios_rd16(bios, data + 0x0e);
			}
			if (*len >= 0x11)
				info->script[4] = nvbios_rd16(bios, data + 0x10);
			break;
		case 0x40:
		case 0x41:
		case 0x42:
			info->flags     = nvbios_rd08(bios, data + 0x04);
			info->script[0] = nvbios_rd16(bios, data + 0x05);
			info->script[1] = nvbios_rd16(bios, data + 0x07);
			info->lnkcmp    = nvbios_rd16(bios, data + 0x09);
			info->script[2] = nvbios_rd16(bios, data + 0x0b);
			info->script[3] = nvbios_rd16(bios, data + 0x0d);
			info->script[4] = nvbios_rd16(bios, data + 0x0f);
			break;
		default:
			data = 0x0000;
			break;
		}
	}
	return data;
}