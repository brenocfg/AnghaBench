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
struct pp_hwmgr {int /*<<< orphan*/ * pptable_func; int /*<<< orphan*/ * hwmgr_func; } ;

/* Variables and functions */
 int /*<<< orphan*/  vega12_hwmgr_funcs ; 
 int /*<<< orphan*/  vega12_pptable_funcs ; 

int vega12_hwmgr_init(struct pp_hwmgr *hwmgr)
{
	hwmgr->hwmgr_func = &vega12_hwmgr_funcs;
	hwmgr->pptable_func = &vega12_pptable_funcs;

	return 0;
}