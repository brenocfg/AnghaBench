#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct panfrost_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS_COMMAND_FLUSH_MEM ; 
 int /*<<< orphan*/  AS_COMMAND_UPDATE ; 
 int /*<<< orphan*/  AS_MEMATTR_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AS_MEMATTR_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AS_TRANSTAB_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AS_TRANSTAB_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_hw_do_operation_locked (struct panfrost_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_write (struct panfrost_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_cmd (struct panfrost_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void panfrost_mmu_disable(struct panfrost_device *pfdev, u32 as_nr)
{
	mmu_hw_do_operation_locked(pfdev, as_nr, 0, ~0UL, AS_COMMAND_FLUSH_MEM);

	mmu_write(pfdev, AS_TRANSTAB_LO(as_nr), 0);
	mmu_write(pfdev, AS_TRANSTAB_HI(as_nr), 0);

	mmu_write(pfdev, AS_MEMATTR_LO(as_nr), 0);
	mmu_write(pfdev, AS_MEMATTR_HI(as_nr), 0);

	write_cmd(pfdev, as_nr, AS_COMMAND_UPDATE);
}