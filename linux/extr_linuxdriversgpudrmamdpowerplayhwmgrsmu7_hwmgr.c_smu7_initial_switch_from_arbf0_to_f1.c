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

/* Variables and functions */
 int /*<<< orphan*/  MC_CG_ARB_FREQ_F0 ; 
 int /*<<< orphan*/  MC_CG_ARB_FREQ_F1 ; 
 int smu7_copy_and_switch_arb_sets (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu7_initial_switch_from_arbf0_to_f1(struct pp_hwmgr *hwmgr)
{
	return smu7_copy_and_switch_arb_sets(hwmgr,
			MC_CG_ARB_FREQ_F0, MC_CG_ARB_FREQ_F1);
}