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
 int nvbios_M0205Ee (struct nvkm_bios*,int,int*,int*,int*,int*) ; 

u32
nvbios_M0205Se(struct nvkm_bios *bios, int ent, int idx, u8 *ver, u8 *hdr)
{

	u8  cnt, len;
	u32 data = nvbios_M0205Ee(bios, ent, ver, hdr, &cnt, &len);
	if (data && idx < cnt) {
		data = data + *hdr + idx * len;
		*hdr = len;
		return data;
	}
	return 0x00000000;
}