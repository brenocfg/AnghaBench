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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct nvkm_bios {int /*<<< orphan*/  subdev; } ;
struct bit_entry {int version; scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  bit_entry (struct nvkm_bios*,char,struct bit_entry*) ; 
 scalar_t__ nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 
 scalar_t__ nvbios_rd32 (struct nvkm_bios*,scalar_t__) ; 
 int /*<<< orphan*/  nvkm_error (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static u32
therm_table(struct nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *len, u8 *cnt)
{
	struct bit_entry bit_P;
	u32 therm = 0;

	if (!bit_entry(bios, 'P', &bit_P)) {
		if (bit_P.version == 1)
			therm = nvbios_rd32(bios, bit_P.offset + 12);
		else if (bit_P.version == 2)
			therm = nvbios_rd32(bios, bit_P.offset + 16);
		else
			nvkm_error(&bios->subdev,
				   "unknown offset for thermal in BIT P %d\n",
				   bit_P.version);
	}

	/* exit now if we haven't found the thermal table */
	if (!therm)
		return 0;

	*ver = nvbios_rd08(bios, therm + 0);
	*hdr = nvbios_rd08(bios, therm + 1);
	*len = nvbios_rd08(bios, therm + 2);
	*cnt = nvbios_rd08(bios, therm + 3);
	return therm + nvbios_rd08(bios, therm + 1);
}