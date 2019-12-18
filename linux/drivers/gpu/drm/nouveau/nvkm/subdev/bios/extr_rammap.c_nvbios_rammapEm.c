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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct nvkm_bios {int dummy; } ;
struct nvbios_ramcfg {scalar_t__ rammap_min; scalar_t__ rammap_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvbios_rammapEp (struct nvkm_bios*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nvbios_ramcfg*) ; 

u32
nvbios_rammapEm(struct nvkm_bios *bios, u16 mhz,
		u8 *ver, u8 *hdr, u8 *cnt, u8 *len, struct nvbios_ramcfg *info)
{
	int idx = 0;
	u32 data;
	while ((data = nvbios_rammapEp(bios, idx++, ver, hdr, cnt, len, info))) {
		if (mhz >= info->rammap_min && mhz <= info->rammap_max)
			break;
	}
	return data;
}