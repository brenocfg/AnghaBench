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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct pp_hwmgr {int dummy; } ;

/* Variables and functions */
 int vega12_copy_table_from_smc (struct pp_hwmgr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vega12_copy_table_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vega12_smc_table_manager(struct pp_hwmgr *hwmgr, uint8_t *table,
				    uint16_t table_id, bool rw)
{
	int ret;

	if (rw)
		ret = vega12_copy_table_from_smc(hwmgr, table, table_id);
	else
		ret = vega12_copy_table_to_smc(hwmgr, table, table_id);

	return ret;
}