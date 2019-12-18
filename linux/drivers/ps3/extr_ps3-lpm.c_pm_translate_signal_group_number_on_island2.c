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
typedef  int u64 ;

/* Variables and functions */
 int PM_ISLAND2_BASE_SIGNAL_GROUP_NUMBER ; 
 int PM_ISLAND2_SIGNAL_GROUP_NUMBER1 ; 
 int PM_ISLAND2_SIGNAL_GROUP_NUMBER2 ; 

__attribute__((used)) static u64 pm_translate_signal_group_number_on_island2(u64 subgroup)
{

	if (subgroup == 2)
		subgroup = 3;

	if (subgroup <= 6)
		return PM_ISLAND2_BASE_SIGNAL_GROUP_NUMBER + subgroup;
	else if (subgroup == 7)
		return PM_ISLAND2_SIGNAL_GROUP_NUMBER1;
	else
		return PM_ISLAND2_SIGNAL_GROUP_NUMBER2;
}