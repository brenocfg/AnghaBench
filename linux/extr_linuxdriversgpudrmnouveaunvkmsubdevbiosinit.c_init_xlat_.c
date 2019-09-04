#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct nvkm_bios {int dummy; } ;
struct nvbios_init {TYPE_2__* subdev; } ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct TYPE_3__ {struct nvkm_bios* bios; } ;

/* Variables and functions */
 int init_xlat_table (struct nvbios_init*) ; 
 int nvbios_rd08 (struct nvkm_bios*,int) ; 
 int nvbios_rd16 (struct nvkm_bios*,int) ; 
 int /*<<< orphan*/  warn (char*,int) ; 

__attribute__((used)) static u8
init_xlat_(struct nvbios_init *init, u8 index, u8 offset)
{
	struct nvkm_bios *bios = init->subdev->device->bios;
	u16 table = init_xlat_table(init);
	if (table) {
		u16 data = nvbios_rd16(bios, table + (index * 2));
		if (data)
			return nvbios_rd08(bios, data + offset);
		warn("xlat table pointer %d invalid\n", index);
	}
	return 0x00;
}