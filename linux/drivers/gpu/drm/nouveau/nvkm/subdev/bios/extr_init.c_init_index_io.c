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
typedef  void* u16 ;
struct nvkm_bios {int dummy; } ;
struct nvbios_init {scalar_t__ offset; TYPE_2__* subdev; } ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct TYPE_3__ {struct nvkm_bios* bios; } ;

/* Variables and functions */
 int init_rdvgai (struct nvbios_init*,void*,int) ; 
 int /*<<< orphan*/  init_wrvgai (struct nvbios_init*,void*,int,int) ; 
 int nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 
 void* nvbios_rd16 (struct nvkm_bios*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,void*,int,int,int) ; 

__attribute__((used)) static void
init_index_io(struct nvbios_init *init)
{
	struct nvkm_bios *bios = init->subdev->device->bios;
	u16 port = nvbios_rd16(bios, init->offset + 1);
	u8 index = nvbios_rd16(bios, init->offset + 3);
	u8  mask = nvbios_rd08(bios, init->offset + 4);
	u8  data = nvbios_rd08(bios, init->offset + 5);
	u8 value;

	trace("INDEX_IO\tI[0x%04x][0x%02x] &= 0x%02x |= 0x%02x\n",
	      port, index, mask, data);
	init->offset += 6;

	value = init_rdvgai(init, port, index) & mask;
	init_wrvgai(init, port, index, data | value);
}