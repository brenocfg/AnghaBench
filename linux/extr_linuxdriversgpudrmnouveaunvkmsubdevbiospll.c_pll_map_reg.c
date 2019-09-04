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
struct pll_mapping {int reg; int type; } ;
struct nvkm_bios {int dummy; } ;

/* Variables and functions */
 int nvbios_rd08 (struct nvkm_bios*,int) ; 
 scalar_t__ nvbios_rd32 (struct nvkm_bios*,int) ; 
 int pll_limits_table (struct nvkm_bios*,int*,int*,int*,int*) ; 
 struct pll_mapping* pll_map (struct nvkm_bios*) ; 

__attribute__((used)) static u32
pll_map_reg(struct nvkm_bios *bios, u32 reg, u32 *type, u8 *ver, u8 *len)
{
	struct pll_mapping *map;
	u8  hdr, cnt;
	u32 data;

	data = pll_limits_table(bios, ver, &hdr, &cnt, len);
	if (data && *ver >= 0x30) {
		data += hdr;
		while (cnt--) {
			if (nvbios_rd32(bios, data + 3) == reg) {
				*type = nvbios_rd08(bios, data + 0);
				return data;
			}
			data += *len;
		}
		return 0x0000;
	}

	map = pll_map(bios);
	while (map && map->reg) {
		if (map->reg == reg && *ver >= 0x20) {
			u32 addr = (data += hdr);
			*type = map->type;
			while (cnt--) {
				if (nvbios_rd32(bios, data) == map->reg)
					return data;
				data += *len;
			}
			return addr;
		} else
		if (map->reg == reg) {
			*type = map->type;
			return data + 1;
		}
		map++;
	}

	return 0x0000;
}