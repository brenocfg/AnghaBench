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
typedef  int u8 ;

/* Variables and functions */
 int QLC_DCB_GET_MAP (int) ; 
 int QLC_DCB_MAX_TC ; 

__attribute__((used)) static int qlcnic_dcb_prio_count(u8 up_tc_map)
{
	int j;

	for (j = 0; j < QLC_DCB_MAX_TC; j++)
		if (up_tc_map & QLC_DCB_GET_MAP(j))
			break;

	return j;
}