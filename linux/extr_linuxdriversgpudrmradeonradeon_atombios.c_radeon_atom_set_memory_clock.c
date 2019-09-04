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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  atom_context; } ;
struct radeon_device {int flags; TYPE_1__ mode_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  ulTargetMemoryClock; } ;
typedef  TYPE_2__ SET_MEMORY_CLOCK_PS_ALLOCATION ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RADEON_IS_IGP ; 
 int /*<<< orphan*/  SetMemoryClock ; 
 int /*<<< orphan*/  atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

void radeon_atom_set_memory_clock(struct radeon_device *rdev,
				  uint32_t mem_clock)
{
	SET_MEMORY_CLOCK_PS_ALLOCATION args;
	int index = GetIndexIntoMasterTable(COMMAND, SetMemoryClock);

	if (rdev->flags & RADEON_IS_IGP)
		return;

	args.ulTargetMemoryClock = cpu_to_le32(mem_clock);	/* 10 khz */

	atom_execute_table(rdev->mode_info.atom_context, index, (uint32_t *)&args);
}