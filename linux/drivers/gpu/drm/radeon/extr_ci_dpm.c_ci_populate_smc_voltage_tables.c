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
struct radeon_device {int dummy; } ;
typedef  int /*<<< orphan*/  SMU7_Discrete_DpmTable ;

/* Variables and functions */
 int ci_populate_smc_mvdd_table (struct radeon_device*,int /*<<< orphan*/ *) ; 
 int ci_populate_smc_vddc_table (struct radeon_device*,int /*<<< orphan*/ *) ; 
 int ci_populate_smc_vddci_table (struct radeon_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ci_populate_smc_voltage_tables(struct radeon_device *rdev,
					  SMU7_Discrete_DpmTable *table)
{
	int ret;

	ret = ci_populate_smc_vddc_table(rdev, table);
	if (ret)
		return ret;

	ret = ci_populate_smc_vddci_table(rdev, table);
	if (ret)
		return ret;

	ret = ci_populate_smc_mvdd_table(rdev, table);
	if (ret)
		return ret;

	return 0;
}