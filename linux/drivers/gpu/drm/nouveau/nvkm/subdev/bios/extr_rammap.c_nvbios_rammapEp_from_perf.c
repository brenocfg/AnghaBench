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
typedef  scalar_t__ u32 ;
struct nvkm_bios {int dummy; } ;
struct nvbios_ramcfg {int rammap_00_16_20; int rammap_00_16_40; int rammap_00_17_02; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct nvbios_ramcfg*,int,int) ; 
 int nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 

u32
nvbios_rammapEp_from_perf(struct nvkm_bios *bios, u32 data, u8 size,
		struct nvbios_ramcfg *p)
{
	memset(p, 0x00, sizeof(*p));

	p->rammap_00_16_20 = (nvbios_rd08(bios, data + 0x16) & 0x20) >> 5;
	p->rammap_00_16_40 = (nvbios_rd08(bios, data + 0x16) & 0x40) >> 6;
	p->rammap_00_17_02 = (nvbios_rd08(bios, data + 0x17) & 0x02) >> 1;

	return data;
}