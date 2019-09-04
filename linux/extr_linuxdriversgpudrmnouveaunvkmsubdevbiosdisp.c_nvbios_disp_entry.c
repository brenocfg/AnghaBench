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

/* Variables and functions */
 int nvbios_disp_table (struct nvkm_bios*,int*,int*,int*,int*,int*) ; 

u16
nvbios_disp_entry(struct nvkm_bios *bios, u8 idx, u8 *ver, u8 *len, u8 *sub)
{
	u8  hdr, cnt;
	u16 data = nvbios_disp_table(bios, ver, &hdr, &cnt, len, sub);
	if (data && idx < cnt)
		return data + hdr + (idx * *len);
	*ver = 0x00;
	return 0x0000;
}