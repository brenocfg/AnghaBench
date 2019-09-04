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
struct nvkm_bios {scalar_t__ bmp_offset; } ;
struct bit_entry {int version; int length; scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  bit_entry (struct nvkm_bios*,char,struct bit_entry*) ; 
 int bmp_version (struct nvkm_bios*) ; 
 int nvbios_rd08 (struct nvkm_bios*,int) ; 
 int nvbios_rd16 (struct nvkm_bios*,scalar_t__) ; 
 int nvbios_rd32 (struct nvkm_bios*,scalar_t__) ; 

__attribute__((used)) static u32
pll_limits_table(struct nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
{
	struct bit_entry bit_C;
	u32 data = 0x0000;

	if (!bit_entry(bios, 'C', &bit_C)) {
		if (bit_C.version == 1 && bit_C.length >= 10)
			data = nvbios_rd16(bios, bit_C.offset + 8);
		if (bit_C.version == 2 && bit_C.length >= 4)
			data = nvbios_rd32(bios, bit_C.offset + 0);
		if (data) {
			*ver = nvbios_rd08(bios, data + 0);
			*hdr = nvbios_rd08(bios, data + 1);
			*len = nvbios_rd08(bios, data + 2);
			*cnt = nvbios_rd08(bios, data + 3);
			return data;
		}
	}

	if (bmp_version(bios) >= 0x0524) {
		data = nvbios_rd16(bios, bios->bmp_offset + 142);
		if (data) {
			*ver = nvbios_rd08(bios, data + 0);
			*hdr = 1;
			*cnt = 1;
			*len = 0x18;
			return data;
		}
	}

	*ver = 0x00;
	return data;
}