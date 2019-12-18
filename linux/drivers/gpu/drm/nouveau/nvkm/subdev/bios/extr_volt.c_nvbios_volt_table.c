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
struct bit_entry {int version; scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  bit_entry (struct nvkm_bios*,char,struct bit_entry*) ; 
 int nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 
 scalar_t__ nvbios_rd32 (struct nvkm_bios*,scalar_t__) ; 

u32
nvbios_volt_table(struct nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
{
	struct bit_entry bit_P;
	u32 volt = 0;

	if (!bit_entry(bios, 'P', &bit_P)) {
		if (bit_P.version == 2)
			volt = nvbios_rd32(bios, bit_P.offset + 0x0c);
		else
		if (bit_P.version == 1)
			volt = nvbios_rd32(bios, bit_P.offset + 0x10);

		if (volt) {
			*ver = nvbios_rd08(bios, volt + 0);
			switch (*ver) {
			case 0x12:
				*hdr = 5;
				*cnt = nvbios_rd08(bios, volt + 2);
				*len = nvbios_rd08(bios, volt + 1);
				return volt;
			case 0x20:
				*hdr = nvbios_rd08(bios, volt + 1);
				*cnt = nvbios_rd08(bios, volt + 2);
				*len = nvbios_rd08(bios, volt + 3);
				return volt;
			case 0x30:
			case 0x40:
			case 0x50:
				*hdr = nvbios_rd08(bios, volt + 1);
				*cnt = nvbios_rd08(bios, volt + 3);
				*len = nvbios_rd08(bios, volt + 2);
				return volt;
			}
		}
	}

	return 0;
}