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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_bios {int dummy; } ;
struct nvbios_init {scalar_t__ offset; TYPE_1__* subdev; } ;
struct TYPE_4__ {struct nvkm_bios* bios; } ;
struct TYPE_3__ {TYPE_2__* device; } ;

/* Variables and functions */
 int init_rdauxr (struct nvbios_init*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_wrauxr (struct nvbios_init*,int /*<<< orphan*/ ,int) ; 
 int nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 
 int /*<<< orphan*/  nvbios_rd32 (struct nvkm_bios*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ,int,...) ; 

__attribute__((used)) static void
init_auxch(struct nvbios_init *init)
{
	struct nvkm_bios *bios = init->subdev->device->bios;
	u32 addr = nvbios_rd32(bios, init->offset + 1);
	u8 count = nvbios_rd08(bios, init->offset + 5);

	trace("AUXCH\tAUX[0x%08x] 0x%02x\n", addr, count);
	init->offset += 6;

	while (count--) {
		u8 mask = nvbios_rd08(bios, init->offset + 0);
		u8 data = nvbios_rd08(bios, init->offset + 1);
		trace("\tAUX[0x%08x] &= 0x%02x |= 0x%02x\n", addr, mask, data);
		mask = init_rdauxr(init, addr) & mask;
		init_wrauxr(init, addr, mask | data);
		init->offset += 2;
	}
}