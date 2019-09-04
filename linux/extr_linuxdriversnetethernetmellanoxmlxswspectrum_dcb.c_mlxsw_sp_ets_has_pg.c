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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 int IEEE_8021QAZ_MAX_TCS ; 

__attribute__((used)) static bool mlxsw_sp_ets_has_pg(u8 *prio_tc, u8 pg)
{
	int i;

	for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
		if (prio_tc[i] == pg)
			return true;
	return false;
}