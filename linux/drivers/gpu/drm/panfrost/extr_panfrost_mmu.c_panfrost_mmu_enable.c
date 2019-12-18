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
typedef  int u64 ;
struct TYPE_2__ {int transtab; int memattr; } ;
struct io_pgtable_cfg {TYPE_1__ arm_mali_lpae_cfg; } ;
struct panfrost_mmu {int as; struct io_pgtable_cfg pgtbl_cfg; } ;
struct panfrost_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS_COMMAND_FLUSH_MEM ; 
 int /*<<< orphan*/  AS_COMMAND_UPDATE ; 
 int /*<<< orphan*/  AS_MEMATTR_HI (int) ; 
 int /*<<< orphan*/  AS_MEMATTR_LO (int) ; 
 int /*<<< orphan*/  AS_TRANSTAB_HI (int) ; 
 int /*<<< orphan*/  AS_TRANSTAB_LO (int) ; 
 int /*<<< orphan*/  mmu_hw_do_operation_locked (struct panfrost_device*,int,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_write (struct panfrost_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_cmd (struct panfrost_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void panfrost_mmu_enable(struct panfrost_device *pfdev, struct panfrost_mmu *mmu)
{
	int as_nr = mmu->as;
	struct io_pgtable_cfg *cfg = &mmu->pgtbl_cfg;
	u64 transtab = cfg->arm_mali_lpae_cfg.transtab;
	u64 memattr = cfg->arm_mali_lpae_cfg.memattr;

	mmu_hw_do_operation_locked(pfdev, as_nr, 0, ~0UL, AS_COMMAND_FLUSH_MEM);

	mmu_write(pfdev, AS_TRANSTAB_LO(as_nr), transtab & 0xffffffffUL);
	mmu_write(pfdev, AS_TRANSTAB_HI(as_nr), transtab >> 32);

	/* Need to revisit mem attrs.
	 * NC is the default, Mali driver is inner WT.
	 */
	mmu_write(pfdev, AS_MEMATTR_LO(as_nr), memattr & 0xffffffffUL);
	mmu_write(pfdev, AS_MEMATTR_HI(as_nr), memattr >> 32);

	write_cmd(pfdev, as_nr, AS_COMMAND_UPDATE);
}