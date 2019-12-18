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
struct nvbios_init {int ramcfg; TYPE_4__* subdev; } ;
struct TYPE_8__ {TYPE_3__* device; } ;
struct TYPE_7__ {TYPE_2__* bios; } ;
struct TYPE_5__ {int major; } ;
struct TYPE_6__ {TYPE_1__ version; } ;

/* Variables and functions */
 int nvbios_ramcfg_index (TYPE_4__*) ; 

__attribute__((used)) static u8
init_ram_restrict(struct nvbios_init *init)
{
	/* This appears to be the behaviour of the VBIOS parser, and *is*
	 * important to cache the NV_PEXTDEV_BOOT0 on later chipsets to
	 * avoid fucking up the memory controller (somehow) by reading it
	 * on every INIT_RAM_RESTRICT_ZM_GROUP opcode.
	 *
	 * Preserving the non-caching behaviour on earlier chipsets just
	 * in case *not* re-reading the strap causes similar breakage.
	 */
	if (!init->ramcfg || init->subdev->device->bios->version.major < 0x70)
		init->ramcfg = 0x80000000 | nvbios_ramcfg_index(init->subdev);
	return (init->ramcfg & 0x7fffffff);
}