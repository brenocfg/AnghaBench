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

/* Variables and functions */
 int dcb_table (struct nvkm_bios*,int*,int*,int*,int*) ; 
 int nvbios_rd08 (struct nvkm_bios*,int) ; 
 int nvbios_rd16 (struct nvkm_bios*,int) ; 

u32
nvbios_connTe(struct nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
{
	u32 dcb = dcb_table(bios, ver, hdr, cnt, len);
	if (dcb && *ver >= 0x30 && *hdr >= 0x16) {
		u32 data = nvbios_rd16(bios, dcb + 0x14);
		if (data) {
			*ver = nvbios_rd08(bios, data + 0);
			*hdr = nvbios_rd08(bios, data + 1);
			*cnt = nvbios_rd08(bios, data + 2);
			*len = nvbios_rd08(bios, data + 3);
			return data;
		}
	}
	return 0x00000000;
}