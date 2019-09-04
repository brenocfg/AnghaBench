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
typedef  int u32 ;
struct nvkm_bios {int dummy; } ;
struct nvbios_init {scalar_t__ offset; TYPE_2__* subdev; } ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct TYPE_3__ {struct nvkm_bios* bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_mask (struct nvbios_init*,int,int,int) ; 
 int /*<<< orphan*/  init_wr32 (struct nvbios_init*,int,int) ; 
 int nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 
 int nvbios_rd32 (struct nvkm_bios*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,int,int) ; 

__attribute__((used)) static void
init_idx_addr_latched(struct nvbios_init *init)
{
	struct nvkm_bios *bios = init->subdev->device->bios;
	u32 creg = nvbios_rd32(bios, init->offset + 1);
	u32 dreg = nvbios_rd32(bios, init->offset + 5);
	u32 mask = nvbios_rd32(bios, init->offset + 9);
	u32 data = nvbios_rd32(bios, init->offset + 13);
	u8 count = nvbios_rd08(bios, init->offset + 17);

	trace("INDEX_ADDRESS_LATCHED\tR[0x%06x] : R[0x%06x]\n", creg, dreg);
	trace("\tCTRL &= 0x%08x |= 0x%08x\n", mask, data);
	init->offset += 18;

	while (count--) {
		u8 iaddr = nvbios_rd08(bios, init->offset + 0);
		u8 idata = nvbios_rd08(bios, init->offset + 1);

		trace("\t[0x%02x] = 0x%02x\n", iaddr, idata);
		init->offset += 2;

		init_wr32(init, dreg, idata);
		init_mask(init, creg, ~mask, data | iaddr);
	}
}