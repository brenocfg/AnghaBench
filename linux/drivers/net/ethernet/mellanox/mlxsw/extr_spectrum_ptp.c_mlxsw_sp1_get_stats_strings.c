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
struct TYPE_2__ {int /*<<< orphan*/  str; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_GSTRING_LEN ; 
 int MLXSW_SP_PTP_PORT_STATS_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* mlxsw_sp_ptp_port_stats ; 

void mlxsw_sp1_get_stats_strings(u8 **p)
{
	int i;

	for (i = 0; i < MLXSW_SP_PTP_PORT_STATS_LEN; i++) {
		memcpy(*p, mlxsw_sp_ptp_port_stats[i].str,
		       ETH_GSTRING_LEN);
		*p += ETH_GSTRING_LEN;
	}
}