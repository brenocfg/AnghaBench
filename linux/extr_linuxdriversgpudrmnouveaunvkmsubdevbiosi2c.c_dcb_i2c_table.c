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
typedef  int u16 ;
struct nvkm_bios {int /*<<< orphan*/  subdev; } ;

/* Variables and functions */
 int dcb_table (struct nvkm_bios*,int*,int*,int*,int*) ; 
 int nvbios_rd08 (struct nvkm_bios*,int) ; 
 int nvbios_rd16 (struct nvkm_bios*,int) ; 
 int /*<<< orphan*/  nvkm_warn (int /*<<< orphan*/ *,char*,int) ; 

u16
dcb_i2c_table(struct nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
{
	u16 i2c = 0x0000;
	u16 dcb = dcb_table(bios, ver, hdr, cnt, len);
	if (dcb) {
		if (*ver >= 0x15)
			i2c = nvbios_rd16(bios, dcb + 2);
		if (*ver >= 0x30)
			i2c = nvbios_rd16(bios, dcb + 4);
	}

	if (i2c && *ver >= 0x42) {
		nvkm_warn(&bios->subdev, "ccb %02x not supported\n", *ver);
		return 0x0000;
	}

	if (i2c && *ver >= 0x30) {
		*ver = nvbios_rd08(bios, i2c + 0);
		*hdr = nvbios_rd08(bios, i2c + 1);
		*cnt = nvbios_rd08(bios, i2c + 2);
		*len = nvbios_rd08(bios, i2c + 3);
	} else {
		*ver = *ver; /* use DCB version */
		*hdr = 0;
		*cnt = 16;
		*len = 4;
	}

	return i2c;
}