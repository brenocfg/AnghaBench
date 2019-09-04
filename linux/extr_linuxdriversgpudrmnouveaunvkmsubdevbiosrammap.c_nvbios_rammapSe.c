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

u32
nvbios_rammapSe(struct nvkm_bios *bios, u32 data,
		u8 ever, u8 ehdr, u8 ecnt, u8 elen, int idx, u8 *ver, u8 *hdr)
{
	if (idx < ecnt) {
		data = data + ehdr + (idx * elen);
		*ver = ever;
		*hdr = elen;
		return data;
	}
	return 0;
}