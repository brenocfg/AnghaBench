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
typedef  scalar_t__ u16 ;
struct nvkm_bios {int dummy; } ;
struct nvbios_init {TYPE_2__* subdev; } ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct TYPE_3__ {struct nvkm_bios* bios; } ;

/* Variables and functions */
 scalar_t__ init_io_condition_table (struct nvbios_init*) ; 
 int init_rdvgai (struct nvbios_init*,scalar_t__,int) ; 
 int nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 
 scalar_t__ nvbios_rd16 (struct nvkm_bios*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,int,scalar_t__,int,int,int) ; 

__attribute__((used)) static bool
init_io_condition_met(struct nvbios_init *init, u8 cond)
{
	struct nvkm_bios *bios = init->subdev->device->bios;
	u16 table = init_io_condition_table(init);
	if (table) {
		u16 port = nvbios_rd16(bios, table + (cond * 5) + 0);
		u8 index = nvbios_rd08(bios, table + (cond * 5) + 2);
		u8  mask = nvbios_rd08(bios, table + (cond * 5) + 3);
		u8 value = nvbios_rd08(bios, table + (cond * 5) + 4);
		trace("\t[0x%02x] (0x%04x[0x%02x] & 0x%02x) == 0x%02x\n",
		      cond, port, index, mask, value);
		return (init_rdvgai(init, port, index) & mask) == value;
	}
	return false;
}