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
typedef  int u32 ;
struct nvkm_bios {int dummy; } ;
struct bit_entry {int version; scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  bit_entry (struct nvkm_bios*,char,struct bit_entry*) ; 
 int /*<<< orphan*/  nvbios_rd08 (struct nvkm_bios*,int) ; 
 int nvbios_rd32 (struct nvkm_bios*,scalar_t__) ; 

u32
nvbios_rammapTe(struct nvkm_bios *bios, u8 *ver, u8 *hdr,
		u8 *cnt, u8 *len, u8 *snr, u8 *ssz)
{
	struct bit_entry bit_P;
	u32 rammap = 0x0000;

	if (!bit_entry(bios, 'P', &bit_P)) {
		if (bit_P.version == 2)
			rammap = nvbios_rd32(bios, bit_P.offset + 4);

		if (rammap) {
			*ver = nvbios_rd08(bios, rammap + 0);
			switch (*ver) {
			case 0x10:
			case 0x11:
				*hdr = nvbios_rd08(bios, rammap + 1);
				*cnt = nvbios_rd08(bios, rammap + 5);
				*len = nvbios_rd08(bios, rammap + 2);
				*snr = nvbios_rd08(bios, rammap + 4);
				*ssz = nvbios_rd08(bios, rammap + 3);
				return rammap;
			default:
				break;
			}
		}
	}

	return 0x0000;
}