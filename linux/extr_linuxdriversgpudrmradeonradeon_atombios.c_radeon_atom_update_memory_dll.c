#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  atom_context; } ;
struct radeon_device {TYPE_1__ mode_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  DynamicMemorySettings ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

void radeon_atom_update_memory_dll(struct radeon_device *rdev,
				   u32 mem_clock)
{
	u32 args;
	int index = GetIndexIntoMasterTable(COMMAND, DynamicMemorySettings);

	args = cpu_to_le32(mem_clock);	/* 10 khz */

	atom_execute_table(rdev->mode_info.atom_context, index, (uint32_t *)&args);
}