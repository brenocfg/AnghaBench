#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct nvkm_bios {int dummy; } ;
struct TYPE_2__ {int freq; } ;
struct nvbios_perfS {TYPE_1__ v40; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct nvbios_perfS*,int,int) ; 
 scalar_t__ nvbios_perfSe (struct nvkm_bios*,scalar_t__,int,int*,int*,int,int) ; 
 int nvbios_rd16 (struct nvkm_bios*,scalar_t__) ; 

u32
nvbios_perfSp(struct nvkm_bios *bios, u32 perfE, int idx,
	      u8 *ver, u8 *hdr, u8 cnt, u8 len,
	      struct nvbios_perfS *info)
{
	u32 data = nvbios_perfSe(bios, perfE, idx, ver, hdr, cnt, len);
	memset(info, 0x00, sizeof(*info));
	switch (!!data * *ver) {
	case 0x40:
		info->v40.freq = (nvbios_rd16(bios, data + 0x00) & 0x3fff) * 1000;
		break;
	default:
		break;
	}
	return data;
}