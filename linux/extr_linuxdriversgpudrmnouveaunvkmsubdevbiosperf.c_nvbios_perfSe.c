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
nvbios_perfSe(struct nvkm_bios *bios, u32 perfE, int idx,
	      u8 *ver, u8 *hdr, u8 cnt, u8 len)
{
	u32 data = 0x00000000;
	if (idx < cnt) {
		data = perfE + *hdr + (idx * len);
		*hdr = len;
	}
	return data;
}