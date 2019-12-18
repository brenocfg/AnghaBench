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
typedef  int u32 ;
struct pmc_dev {TYPE_1__* map; } ;
struct TYPE_2__ {int /*<<< orphan*/  pm_read_disable_bit; int /*<<< orphan*/  pm_cfg_offset; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 struct pmc_dev pmc ; 
 int pmc_core_reg_read (struct pmc_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pmc_core_check_read_lock_bit(void)
{
	struct pmc_dev *pmcdev = &pmc;
	u32 value;

	value = pmc_core_reg_read(pmcdev, pmcdev->map->pm_cfg_offset);
	return value & BIT(pmcdev->map->pm_read_disable_bit);
}