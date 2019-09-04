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
 int nvbios_connTe (struct nvkm_bios*,int*,int*,int*,int*) ; 

u32
nvbios_connEe(struct nvkm_bios *bios, u8 idx, u8 *ver, u8 *len)
{
	u8  hdr, cnt;
	u32 data = nvbios_connTe(bios, ver, &hdr, &cnt, len);
	if (data && idx < cnt)
		return data + hdr + (idx * *len);
	return 0x00000000;
}