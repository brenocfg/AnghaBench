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
typedef  int /*<<< orphan*/  SMU71_Discrete_Ulv ;

/* Variables and functions */
 int iceland_populate_ulv_level (struct pp_hwmgr*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iceland_populate_ulv_state(struct pp_hwmgr *hwmgr,
		 SMU71_Discrete_Ulv *ulv_level)
{
	return iceland_populate_ulv_level(hwmgr, ulv_level);
}