#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_8__ {TYPE_3__* device; } ;
struct nvkm_bios {TYPE_4__ subdev; } ;
struct nvbios_init {scalar_t__ offset; TYPE_2__* subdev; } ;
struct TYPE_7__ {scalar_t__ card_type; } ;
struct TYPE_6__ {TYPE_1__* device; } ;
struct TYPE_5__ {struct nvkm_bios* bios; } ;

/* Variables and functions */
 scalar_t__ NV_50 ; 
 int /*<<< orphan*/  init_mask (struct nvbios_init*,int,int,int) ; 
 int init_rdport (struct nvbios_init*,int) ; 
 int /*<<< orphan*/  init_wr32 (struct nvbios_init*,int,int) ; 
 int /*<<< orphan*/  init_wrport (struct nvbios_init*,int,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int nvbios_rd16 (struct nvkm_bios*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,int,int,int) ; 

__attribute__((used)) static void
init_io(struct nvbios_init *init)
{
	struct nvkm_bios *bios = init->subdev->device->bios;
	u16 port = nvbios_rd16(bios, init->offset + 1);
	u8  mask = nvbios_rd16(bios, init->offset + 3);
	u8  data = nvbios_rd16(bios, init->offset + 4);
	u8 value;

	trace("IO\t\tI[0x%04x] &= 0x%02x |= 0x%02x\n", port, mask, data);
	init->offset += 5;

	/* ummm.. yes.. should really figure out wtf this is and why it's
	 * needed some day..  it's almost certainly wrong, but, it also
	 * somehow makes things work...
	 */
	if (bios->subdev.device->card_type >= NV_50 &&
	    port == 0x03c3 && data == 0x01) {
		init_mask(init, 0x614100, 0xf0800000, 0x00800000);
		init_mask(init, 0x00e18c, 0x00020000, 0x00020000);
		init_mask(init, 0x614900, 0xf0800000, 0x00800000);
		init_mask(init, 0x000200, 0x40000000, 0x00000000);
		mdelay(10);
		init_mask(init, 0x00e18c, 0x00020000, 0x00000000);
		init_mask(init, 0x000200, 0x40000000, 0x40000000);
		init_wr32(init, 0x614100, 0x00800018);
		init_wr32(init, 0x614900, 0x00800018);
		mdelay(10);
		init_wr32(init, 0x614100, 0x10000018);
		init_wr32(init, 0x614900, 0x10000018);
	}

	value = init_rdport(init, port) & mask;
	init_wrport(init, port, data | value);
}