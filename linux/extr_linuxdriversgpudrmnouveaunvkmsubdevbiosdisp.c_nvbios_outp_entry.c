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
typedef  scalar_t__ u16 ;
struct nvkm_bios {int dummy; } ;
struct nvbios_disp {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ nvbios_disp_parse (struct nvkm_bios*,int,int*,int*,int*,struct nvbios_disp*) ; 
 int nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 

u16
nvbios_outp_entry(struct nvkm_bios *bios, u8 idx,
		  u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
{
	struct nvbios_disp info;
	u16 data = nvbios_disp_parse(bios, idx, ver, len, hdr, &info);
	if (data) {
		*cnt = nvbios_rd08(bios, info.data + 0x05);
		*len = 0x06;
		data = info.data;
	}
	return data;
}