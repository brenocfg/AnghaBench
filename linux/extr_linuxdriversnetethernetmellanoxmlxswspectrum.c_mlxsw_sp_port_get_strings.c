#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  str; } ;
struct TYPE_3__ {int /*<<< orphan*/  str; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_GSTRING_LEN ; 
#define  ETH_SS_STATS 128 
 int IEEE_8021QAZ_MAX_TCS ; 
 int MLXSW_SP_PORT_HW_RFC_2819_STATS_LEN ; 
 int MLXSW_SP_PORT_HW_STATS_LEN ; 
 int TC_MAX_QUEUE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_port_get_prio_strings (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  mlxsw_sp_port_get_tc_strings (int /*<<< orphan*/ **,int) ; 
 TYPE_2__* mlxsw_sp_port_hw_rfc_2819_stats ; 
 TYPE_1__* mlxsw_sp_port_hw_stats ; 

__attribute__((used)) static void mlxsw_sp_port_get_strings(struct net_device *dev,
				      u32 stringset, u8 *data)
{
	u8 *p = data;
	int i;

	switch (stringset) {
	case ETH_SS_STATS:
		for (i = 0; i < MLXSW_SP_PORT_HW_STATS_LEN; i++) {
			memcpy(p, mlxsw_sp_port_hw_stats[i].str,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		}
		for (i = 0; i < MLXSW_SP_PORT_HW_RFC_2819_STATS_LEN; i++) {
			memcpy(p, mlxsw_sp_port_hw_rfc_2819_stats[i].str,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		}

		for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
			mlxsw_sp_port_get_prio_strings(&p, i);

		for (i = 0; i < TC_MAX_QUEUE; i++)
			mlxsw_sp_port_get_tc_strings(&p, i);

		break;
	}
}