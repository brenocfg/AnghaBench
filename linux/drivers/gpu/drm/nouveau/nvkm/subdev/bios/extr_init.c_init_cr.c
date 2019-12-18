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
struct nvkm_bios {int dummy; } ;
struct nvbios_init {scalar_t__ offset; TYPE_2__* subdev; } ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct TYPE_3__ {struct nvkm_bios* bios; } ;

/* Variables and functions */
 int init_rdvgai (struct nvbios_init*,int,int) ; 
 int /*<<< orphan*/  init_wrvgai (struct nvbios_init*,int,int,int) ; 
 int nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,int,int,int) ; 

__attribute__((used)) static void
init_cr(struct nvbios_init *init)
{
	struct nvkm_bios *bios = init->subdev->device->bios;
	u8 addr = nvbios_rd08(bios, init->offset + 1);
	u8 mask = nvbios_rd08(bios, init->offset + 2);
	u8 data = nvbios_rd08(bios, init->offset + 3);
	u8 val;

	trace("CR\t\tC[0x%02x] &= 0x%02x |= 0x%02x\n", addr, mask, data);
	init->offset += 4;

	val = init_rdvgai(init, 0x03d4, addr) & mask;
	init_wrvgai(init, 0x03d4, addr, val | data);
}