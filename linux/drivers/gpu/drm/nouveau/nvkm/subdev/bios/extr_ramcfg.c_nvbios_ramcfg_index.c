#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct nvkm_subdev {TYPE_1__* device; } ;
struct nvkm_bios {int dummy; } ;
struct nvbios_M0203E {int group; } ;
struct bit_entry {int version; int length; scalar_t__ offset; } ;
struct TYPE_2__ {struct nvkm_bios* bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  bit_entry (struct nvkm_bios*,char,struct bit_entry*) ; 
 scalar_t__ nvbios_M0203Em (struct nvkm_bios*,int,int*,int*,struct nvbios_M0203E*) ; 
 int nvbios_ramcfg_strap (struct nvkm_subdev*) ; 
 int nvbios_rd08 (struct nvkm_bios*,int) ; 
 int nvbios_rd16 (struct nvkm_bios*,scalar_t__) ; 

u8
nvbios_ramcfg_index(struct nvkm_subdev *subdev)
{
	struct nvkm_bios *bios = subdev->device->bios;
	u8 strap = nvbios_ramcfg_strap(subdev);
	u32 xlat = 0x00000000;
	struct bit_entry bit_M;
	struct nvbios_M0203E M0203E;
	u8 ver, hdr;

	if (!bit_entry(bios, 'M', &bit_M)) {
		if (bit_M.version == 1 && bit_M.length >= 5)
			xlat = nvbios_rd16(bios, bit_M.offset + 3);
		if (bit_M.version == 2 && bit_M.length >= 3) {
			/*XXX: is M ever shorter than this?
			 *     if not - what is xlat used for now?
			 *     also - sigh..
			 */
			if (bit_M.length >= 7 &&
			    nvbios_M0203Em(bios, strap, &ver, &hdr, &M0203E))
				return M0203E.group;
			xlat = nvbios_rd16(bios, bit_M.offset + 1);
		}
	}

	if (xlat)
		strap = nvbios_rd08(bios, xlat + strap);
	return strap;
}