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
typedef  scalar_t__ u32 ;
struct nvkm_bios {int dummy; } ;
struct nvbios_vmap_entry {int link; void** arg; void* max; void* min; void* mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct nvbios_vmap_entry*,int,int) ; 
 void* nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 
 void* nvbios_rd32 (struct nvkm_bios*,scalar_t__) ; 
 scalar_t__ nvbios_vmap_entry (struct nvkm_bios*,int,int*,int*) ; 

u32
nvbios_vmap_entry_parse(struct nvkm_bios *bios, int idx, u8 *ver, u8 *len,
			struct nvbios_vmap_entry *info)
{
	u32 vmap = nvbios_vmap_entry(bios, idx, ver, len);
	memset(info, 0x00, sizeof(*info));
	switch (!!vmap * *ver) {
	case 0x10:
		info->link   = 0xff;
		info->min    = nvbios_rd32(bios, vmap + 0x00);
		info->max    = nvbios_rd32(bios, vmap + 0x04);
		info->arg[0] = nvbios_rd32(bios, vmap + 0x08);
		info->arg[1] = nvbios_rd32(bios, vmap + 0x0c);
		info->arg[2] = nvbios_rd32(bios, vmap + 0x10);
		break;
	case 0x20:
		info->mode   = nvbios_rd08(bios, vmap + 0x00);
		info->link   = nvbios_rd08(bios, vmap + 0x01);
		info->min    = nvbios_rd32(bios, vmap + 0x02);
		info->max    = nvbios_rd32(bios, vmap + 0x06);
		info->arg[0] = nvbios_rd32(bios, vmap + 0x0a);
		info->arg[1] = nvbios_rd32(bios, vmap + 0x0e);
		info->arg[2] = nvbios_rd32(bios, vmap + 0x12);
		info->arg[3] = nvbios_rd32(bios, vmap + 0x16);
		info->arg[4] = nvbios_rd32(bios, vmap + 0x1a);
		info->arg[5] = nvbios_rd32(bios, vmap + 0x1e);
		break;
	}
	return vmap;
}