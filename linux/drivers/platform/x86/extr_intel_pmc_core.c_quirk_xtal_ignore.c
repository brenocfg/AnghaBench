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
typedef  int /*<<< orphan*/  u32 ;
struct pmc_dev {TYPE_1__* map; } ;
struct dmi_system_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pm_vric1_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPT_PMC_VRIC1_SLPS0LVEN ; 
 int /*<<< orphan*/  SPT_PMC_VRIC1_XTALSDQDIS ; 
 struct pmc_dev pmc ; 
 int /*<<< orphan*/  pmc_core_reg_read (struct pmc_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmc_core_reg_write (struct pmc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int quirk_xtal_ignore(const struct dmi_system_id *id)
{
	struct pmc_dev *pmcdev = &pmc;
	u32 value;

	value = pmc_core_reg_read(pmcdev, pmcdev->map->pm_vric1_offset);
	/* 24MHz Crystal Shutdown Qualification Disable */
	value |= SPT_PMC_VRIC1_XTALSDQDIS;
	/* Low Voltage Mode Enable */
	value &= ~SPT_PMC_VRIC1_SLPS0LVEN;
	pmc_core_reg_write(pmcdev, pmcdev->map->pm_vric1_offset, value);
	return 0;
}