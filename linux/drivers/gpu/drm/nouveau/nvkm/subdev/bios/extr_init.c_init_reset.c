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
typedef  int u32 ;
struct nvkm_bios {int dummy; } ;
struct nvbios_init {scalar_t__ offset; TYPE_2__* subdev; } ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct TYPE_3__ {struct nvkm_bios* bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_exec_force (struct nvbios_init*,int) ; 
 int init_mask (struct nvbios_init*,int,int,int) ; 
 int /*<<< orphan*/  init_wr32 (struct nvbios_init*,int,int) ; 
 int nvbios_rd32 (struct nvkm_bios*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,int,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
init_reset(struct nvbios_init *init)
{
	struct nvkm_bios *bios = init->subdev->device->bios;
	u32   reg = nvbios_rd32(bios, init->offset + 1);
	u32 data1 = nvbios_rd32(bios, init->offset + 5);
	u32 data2 = nvbios_rd32(bios, init->offset + 9);
	u32 savepci19;

	trace("RESET\tR[0x%08x] = 0x%08x, 0x%08x", reg, data1, data2);
	init->offset += 13;
	init_exec_force(init, true);

	savepci19 = init_mask(init, 0x00184c, 0x00000f00, 0x00000000);
	init_wr32(init, reg, data1);
	udelay(10);
	init_wr32(init, reg, data2);
	init_wr32(init, 0x00184c, savepci19);
	init_mask(init, 0x001850, 0x00000001, 0x00000000);

	init_exec_force(init, false);
}