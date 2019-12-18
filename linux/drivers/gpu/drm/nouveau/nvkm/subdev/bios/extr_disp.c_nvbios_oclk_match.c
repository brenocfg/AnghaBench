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
typedef  int u32 ;
typedef  int u16 ;
struct nvkm_bios {int dummy; } ;

/* Variables and functions */
 int nvbios_rd16 (struct nvkm_bios*,int) ; 

u16
nvbios_oclk_match(struct nvkm_bios *bios, u16 cmp, u32 khz)
{
	while (cmp) {
		if (khz / 10 >= nvbios_rd16(bios, cmp + 0x00))
			return  nvbios_rd16(bios, cmp + 0x02);
		cmp += 0x04;
	}
	return 0x0000;
}