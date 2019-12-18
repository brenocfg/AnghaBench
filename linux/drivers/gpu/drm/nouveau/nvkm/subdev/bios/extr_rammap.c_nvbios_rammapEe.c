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
 int nvbios_rammapTe (struct nvkm_bios*,int*,int*,int*,int*,int*,int*) ; 

u32
nvbios_rammapEe(struct nvkm_bios *bios, int idx,
		u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
{
	u8  snr, ssz;
	u32 rammap = nvbios_rammapTe(bios, ver, hdr, cnt, len, &snr, &ssz);
	if (rammap && idx < *cnt) {
		rammap = rammap + *hdr + (idx * (*len + (snr * ssz)));
		*hdr = *len;
		*cnt = snr;
		*len = ssz;
		return rammap;
	}
	return 0x0000;
}