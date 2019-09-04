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
struct pp_hwmgr {int dummy; } ;
struct SMU74_Discrete_DpmTable {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  polaris10_populate_cac_table (struct pp_hwmgr*,struct SMU74_Discrete_DpmTable*) ; 
 int /*<<< orphan*/  polaris10_populate_smc_mvdd_table (struct pp_hwmgr*,struct SMU74_Discrete_DpmTable*) ; 
 int /*<<< orphan*/  polaris10_populate_smc_vddci_table (struct pp_hwmgr*,struct SMU74_Discrete_DpmTable*) ; 

__attribute__((used)) static int polaris10_populate_smc_voltage_tables(struct pp_hwmgr *hwmgr,
		struct SMU74_Discrete_DpmTable *table)
{
	polaris10_populate_smc_vddci_table(hwmgr, table);
	polaris10_populate_smc_mvdd_table(hwmgr, table);
	polaris10_populate_cac_table(hwmgr, table);

	return 0;
}