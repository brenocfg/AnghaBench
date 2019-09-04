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
struct nvkm_bios {scalar_t__ bmp_offset; } ;
struct bit_entry {int version; scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  bit_entry (struct nvkm_bios*,char,struct bit_entry*) ; 
 int nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 
 scalar_t__ nvbios_rd16 (struct nvkm_bios*,scalar_t__) ; 
 scalar_t__ nvbios_rd32 (struct nvkm_bios*,scalar_t__) ; 

u32
nvbios_perf_table(struct nvkm_bios *bios, u8 *ver, u8 *hdr,
		  u8 *cnt, u8 *len, u8 *snr, u8 *ssz)
{
	struct bit_entry bit_P;
	u32 perf = 0;

	if (!bit_entry(bios, 'P', &bit_P)) {
		if (bit_P.version <= 2) {
			perf = nvbios_rd32(bios, bit_P.offset + 0);
			if (perf) {
				*ver = nvbios_rd08(bios, perf + 0);
				*hdr = nvbios_rd08(bios, perf + 1);
				if (*ver >= 0x40 && *ver < 0x41) {
					*cnt = nvbios_rd08(bios, perf + 5);
					*len = nvbios_rd08(bios, perf + 2);
					*snr = nvbios_rd08(bios, perf + 4);
					*ssz = nvbios_rd08(bios, perf + 3);
					return perf;
				} else
				if (*ver >= 0x20 && *ver < 0x40) {
					*cnt = nvbios_rd08(bios, perf + 2);
					*len = nvbios_rd08(bios, perf + 3);
					*snr = nvbios_rd08(bios, perf + 4);
					*ssz = nvbios_rd08(bios, perf + 5);
					return perf;
				}
			}
		}
	}

	if (bios->bmp_offset) {
		if (nvbios_rd08(bios, bios->bmp_offset + 6) >= 0x25) {
			perf = nvbios_rd16(bios, bios->bmp_offset + 0x94);
			if (perf) {
				*hdr = nvbios_rd08(bios, perf + 0);
				*ver = nvbios_rd08(bios, perf + 1);
				*cnt = nvbios_rd08(bios, perf + 2);
				*len = nvbios_rd08(bios, perf + 3);
				*snr = 0;
				*ssz = 0;
				return perf;
			}
		}
	}

	return 0;
}