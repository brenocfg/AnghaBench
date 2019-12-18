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
typedef  int /*<<< orphan*/  uint32_t ;
struct pp_hwmgr {TYPE_1__* hwmgr_func; } ;
struct TYPE_2__ {int (* set_min_deep_sleep_dcefclk ) (struct pp_hwmgr*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PHM_FUNC_CHECK (struct pp_hwmgr*) ; 
 int stub1 (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

int phm_set_min_deep_sleep_dcefclk(struct pp_hwmgr *hwmgr, uint32_t clock)
{
	PHM_FUNC_CHECK(hwmgr);

	if (!hwmgr->hwmgr_func->set_min_deep_sleep_dcefclk)
		return -EINVAL;

	return hwmgr->hwmgr_func->set_min_deep_sleep_dcefclk(hwmgr, clock);
}