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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct nvkm_bios {int dummy; } ;
struct nvbios_init {scalar_t__ offset; TYPE_2__* subdev; } ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct TYPE_3__ {struct nvkm_bios* bios; } ;

/* Variables and functions */
 scalar_t__ init_tmds_reg (struct nvbios_init*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_wr32 (struct nvbios_init*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
init_zm_tmds_group(struct nvbios_init *init)
{
	struct nvkm_bios *bios = init->subdev->device->bios;
	u8  tmds = nvbios_rd08(bios, init->offset + 1);
	u8 count = nvbios_rd08(bios, init->offset + 2);
	u32  reg = init_tmds_reg(init, tmds);

	trace("TMDS_ZM_GROUP\tT[0x%02x]\n", tmds);
	init->offset += 3;

	while (count--) {
		u8 addr = nvbios_rd08(bios, init->offset + 0);
		u8 data = nvbios_rd08(bios, init->offset + 1);

		trace("\t[0x%02x] = 0x%02x\n", addr, data);
		init->offset += 2;

		init_wr32(init, reg + 4, data);
		init_wr32(init, reg + 0, addr);
	}
}