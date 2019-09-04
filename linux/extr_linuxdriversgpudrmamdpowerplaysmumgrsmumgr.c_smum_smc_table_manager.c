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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct pp_hwmgr {TYPE_1__* smumgr_funcs; } ;
struct TYPE_2__ {int (* smc_table_manager ) (struct pp_hwmgr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct pp_hwmgr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int smum_smc_table_manager(struct pp_hwmgr *hwmgr, uint8_t *table, uint16_t table_id, bool rw)
{
	if (hwmgr->smumgr_funcs->smc_table_manager)
		return hwmgr->smumgr_funcs->smc_table_manager(hwmgr, table, table_id, rw);

	return -EINVAL;
}