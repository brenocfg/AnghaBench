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
struct nvbios_dpcfg {void* tx_pu; void* pe; void* dc; void* pc; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct nvbios_dpcfg*,int,int) ; 
 int nvbios_dpcfg_entry (struct nvkm_bios*,int,int,int*,int*,int*,int*) ; 
 void* nvbios_rd08 (struct nvkm_bios*,int) ; 

u16
nvbios_dpcfg_parse(struct nvkm_bios *bios, u16 outp, u8 idx,
		   u8 *ver, u8 *hdr, u8 *cnt, u8 *len,
		   struct nvbios_dpcfg *info)
{
	u16 data = nvbios_dpcfg_entry(bios, outp, idx, ver, hdr, cnt, len);
	memset(info, 0x00, sizeof(*info));
	if (data) {
		switch (*ver) {
		case 0x20:
		case 0x21:
			info->dc    = nvbios_rd08(bios, data + 0x02);
			info->pe    = nvbios_rd08(bios, data + 0x03);
			info->tx_pu = nvbios_rd08(bios, data + 0x04);
			break;
		case 0x30:
		case 0x40:
		case 0x41:
			info->pc    = nvbios_rd08(bios, data + 0x00);
			info->dc    = nvbios_rd08(bios, data + 0x01);
			info->pe    = nvbios_rd08(bios, data + 0x02);
			info->tx_pu = nvbios_rd08(bios, data + 0x03);
			break;
		case 0x42:
			info->dc    = nvbios_rd08(bios, data + 0x00);
			info->pe    = nvbios_rd08(bios, data + 0x01);
			info->tx_pu = nvbios_rd08(bios, data + 0x02);
			break;
		default:
			data = 0x0000;
			break;
		}
	}
	return data;
}