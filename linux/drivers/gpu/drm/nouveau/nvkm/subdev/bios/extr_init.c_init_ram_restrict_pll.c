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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct nvkm_bios {int dummy; } ;
struct nvbios_init {scalar_t__ offset; TYPE_2__* subdev; } ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct TYPE_3__ {struct nvkm_bios* bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_prog_pll (struct nvbios_init*,scalar_t__,scalar_t__) ; 
 scalar_t__ init_ram_restrict (struct nvbios_init*) ; 
 scalar_t__ init_ram_restrict_group_count (struct nvbios_init*) ; 
 scalar_t__ nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 
 scalar_t__ nvbios_rd32 (struct nvkm_bios*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,scalar_t__) ; 

__attribute__((used)) static void
init_ram_restrict_pll(struct nvbios_init *init)
{
	struct nvkm_bios *bios = init->subdev->device->bios;
	u8  type = nvbios_rd08(bios, init->offset + 1);
	u8 count = init_ram_restrict_group_count(init);
	u8 strap = init_ram_restrict(init);
	u8 cconf;

	trace("RAM_RESTRICT_PLL\t0x%02x\n", type);
	init->offset += 2;

	for (cconf = 0; cconf < count; cconf++) {
		u32 freq = nvbios_rd32(bios, init->offset);

		if (cconf == strap) {
			trace("%dkHz *\n", freq);
			init_prog_pll(init, type, freq);
		} else {
			trace("%dkHz\n", freq);
		}

		init->offset += 4;
	}
}