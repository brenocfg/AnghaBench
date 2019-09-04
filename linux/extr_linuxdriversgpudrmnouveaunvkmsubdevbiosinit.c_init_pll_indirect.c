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
typedef  scalar_t__ u16 ;
struct nvkm_bios {int dummy; } ;
struct nvbios_init {scalar_t__ offset; TYPE_2__* subdev; } ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct TYPE_3__ {struct nvkm_bios* bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_prog_pll (struct nvbios_init*,int,int) ; 
 scalar_t__ nvbios_rd16 (struct nvkm_bios*,scalar_t__) ; 
 int nvbios_rd32 (struct nvkm_bios*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,int,scalar_t__,int) ; 

__attribute__((used)) static void
init_pll_indirect(struct nvbios_init *init)
{
	struct nvkm_bios *bios = init->subdev->device->bios;
	u32  reg = nvbios_rd32(bios, init->offset + 1);
	u16 addr = nvbios_rd16(bios, init->offset + 5);
	u32 freq = (u32)nvbios_rd16(bios, addr) * 1000;

	trace("PLL_INDIRECT\tR[0x%06x] =PLL= VBIOS[%04x] = %dkHz\n",
	      reg, addr, freq);
	init->offset += 7;

	init_prog_pll(init, reg, freq);
}