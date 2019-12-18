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
struct pp_smu {int dummy; } ;
struct dpm_clocks {int dummy; } ;
typedef  enum pp_smu_status { ____Placeholder_pp_smu_status } pp_smu_status ;

/* Variables and functions */
 int PP_SMU_RESULT_OK ; 
 struct dpm_clocks dummy_clocks ; 

enum pp_smu_status dummy_get_dpm_clock_table(struct pp_smu *pp,
		struct dpm_clocks *clock_table)
{
	*clock_table = dummy_clocks;
	return PP_SMU_RESULT_OK;
}