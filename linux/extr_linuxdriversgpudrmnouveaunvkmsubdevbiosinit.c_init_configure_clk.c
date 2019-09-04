#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_4__ {int major; } ;
struct nvkm_bios {TYPE_1__ version; } ;
struct nvbios_init {int offset; TYPE_3__* subdev; } ;
struct TYPE_6__ {TYPE_2__* device; } ;
struct TYPE_5__ {struct nvkm_bios* bios; } ;

/* Variables and functions */
 int init_configure_mem_clk (struct nvbios_init*) ; 
 int /*<<< orphan*/  init_done (struct nvbios_init*) ; 
 int /*<<< orphan*/  init_exec_force (struct nvbios_init*,int) ; 
 int /*<<< orphan*/  init_prog_pll (struct nvbios_init*,int,int) ; 
 int nvbios_rd08 (struct nvkm_bios*,int) ; 
 int nvbios_rd16 (struct nvkm_bios*,int) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void
init_configure_clk(struct nvbios_init *init)
{
	struct nvkm_bios *bios = init->subdev->device->bios;
	u16 mdata, clock;

	trace("CONFIGURE_CLK\n");
	init->offset += 1;

	if (bios->version.major > 2) {
		init_done(init);
		return;
	}
	init_exec_force(init, true);

	mdata = init_configure_mem_clk(init);

	/* NVPLL */
	clock = nvbios_rd16(bios, mdata + 4) * 10;
	init_prog_pll(init, 0x680500, clock);

	/* MPLL */
	clock = nvbios_rd16(bios, mdata + 2) * 10;
	if (nvbios_rd08(bios, mdata) & 0x01)
		clock *= 2;
	init_prog_pll(init, 0x680504, clock);

	init_exec_force(init, false);
}