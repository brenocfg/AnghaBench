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
struct nvbios_init {TYPE_2__* subdev; } ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct TYPE_3__ {int /*<<< orphan*/  bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvbios_ramcfg_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8
init_ram_restrict_group_count(struct nvbios_init *init)
{
	return nvbios_ramcfg_count(init->subdev->device->bios);
}