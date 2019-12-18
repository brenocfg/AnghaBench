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
 int nvbios_vmap_table (struct nvkm_bios*,int*,int*,int*,int*) ; 

u32
nvbios_vmap_entry(struct nvkm_bios *bios, int idx, u8 *ver, u8 *len)
{
	u8  hdr, cnt;
	u32 vmap = nvbios_vmap_table(bios, ver, &hdr, &cnt, len);
	if (vmap && idx < cnt) {
		vmap = vmap + hdr + (idx * *len);
		return vmap;
	}
	return 0;
}