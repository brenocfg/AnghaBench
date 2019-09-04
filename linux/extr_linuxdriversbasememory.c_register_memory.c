#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int id; int offline; int /*<<< orphan*/  groups; int /*<<< orphan*/  release; int /*<<< orphan*/ * bus; } ;
struct memory_block {int start_section_nr; scalar_t__ state; TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ MEM_OFFLINE ; 
 int device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  memory_block_release ; 
 int /*<<< orphan*/  memory_memblk_attr_groups ; 
 int /*<<< orphan*/  memory_subsys ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int sections_per_block ; 

__attribute__((used)) static
int register_memory(struct memory_block *memory)
{
	int ret;

	memory->dev.bus = &memory_subsys;
	memory->dev.id = memory->start_section_nr / sections_per_block;
	memory->dev.release = memory_block_release;
	memory->dev.groups = memory_memblk_attr_groups;
	memory->dev.offline = memory->state == MEM_OFFLINE;

	ret = device_register(&memory->dev);
	if (ret)
		put_device(&memory->dev);

	return ret;
}