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
struct pp_hwmgr {TYPE_1__* smumgr_funcs; } ;
struct TYPE_2__ {int (* smu_init ) (struct pp_hwmgr*) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  phm_register_irq_handlers (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int stub1 (struct pp_hwmgr*) ; 

int hwmgr_sw_init(struct pp_hwmgr *hwmgr)
{
	if (!hwmgr|| !hwmgr->smumgr_funcs || !hwmgr->smumgr_funcs->smu_init)
		return -EINVAL;

	phm_register_irq_handlers(hwmgr);
	pr_info("hwmgr_sw_init smu backed is %s\n", hwmgr->smumgr_funcs->name);

	return hwmgr->smumgr_funcs->smu_init(hwmgr);
}