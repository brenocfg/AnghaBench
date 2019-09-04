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
struct bit_entry {int version; int length; scalar_t__ offset; } ;

/* Variables and functions */
 scalar_t__ bit_entry (struct nvkm_bios*,char,struct bit_entry*) ; 
 int /*<<< orphan*/  nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 
 scalar_t__ nvbios_rd32 (struct nvkm_bios*,scalar_t__) ; 

__attribute__((used)) static u32
nvbios_iccsense_table(struct nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt,
		      u8 *len)
{
	struct bit_entry bit_P;
	u32 iccsense;

	if (bit_entry(bios, 'P', &bit_P) || bit_P.version != 2 ||
	    bit_P.length < 0x2c)
		return 0;

	iccsense = nvbios_rd32(bios, bit_P.offset + 0x28);
	if (!iccsense)
		return 0;

	*ver = nvbios_rd08(bios, iccsense + 0);
	switch (*ver) {
	case 0x10:
	case 0x20:
		*hdr = nvbios_rd08(bios, iccsense + 1);
		*len = nvbios_rd08(bios, iccsense + 2);
		*cnt = nvbios_rd08(bios, iccsense + 3);
		return iccsense;
	default:
		break;
	}

	return 0;
}