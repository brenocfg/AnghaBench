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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {char* str; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_GSTRING_LEN ; 
 int MLXSW_SP_PORT_HW_TC_STATS_LEN ; 
 TYPE_1__* mlxsw_sp_port_hw_tc_stats ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,int) ; 

__attribute__((used)) static void mlxsw_sp_port_get_tc_strings(u8 **p, int tc)
{
	int i;

	for (i = 0; i < MLXSW_SP_PORT_HW_TC_STATS_LEN; i++) {
		snprintf(*p, ETH_GSTRING_LEN, "%.29s_%.1d",
			 mlxsw_sp_port_hw_tc_stats[i].str, tc);
		*p += ETH_GSTRING_LEN;
	}
}