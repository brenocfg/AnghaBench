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
struct nvbios_P0260E {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct nvbios_P0260E*,int,int) ; 
 int nvbios_P0260Ee (struct nvkm_bios*,int,int*,int*) ; 
 int /*<<< orphan*/  nvbios_rd32 (struct nvkm_bios*,int) ; 

u32
nvbios_P0260Ep(struct nvkm_bios *bios, int idx, u8 *ver, u8 *len,
	       struct nvbios_P0260E *info)
{
	u32 data = nvbios_P0260Ee(bios, idx, ver, len);
	memset(info, 0x00, sizeof(*info));
	switch (!!data * *ver) {
	case 0x10:
		info->data = nvbios_rd32(bios, data);
		return data;
	default:
		break;
	}
	return 0x00000000;
}