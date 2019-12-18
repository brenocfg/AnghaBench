#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct mlxsw_sp_port {TYPE_2__* mlxsw_sp; } ;
struct TYPE_14__ {int /*<<< orphan*/  str; } ;
struct TYPE_13__ {int /*<<< orphan*/  str; } ;
struct TYPE_12__ {int /*<<< orphan*/  str; } ;
struct TYPE_11__ {int /*<<< orphan*/  str; } ;
struct TYPE_10__ {int /*<<< orphan*/  str; } ;
struct TYPE_9__ {TYPE_1__* ptp_ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* get_stats_strings ) (int /*<<< orphan*/ **) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_GSTRING_LEN ; 
#define  ETH_SS_STATS 128 
 int IEEE_8021QAZ_MAX_TCS ; 
 int MLXSW_SP_PORT_HW_DISCARD_STATS_LEN ; 
 int MLXSW_SP_PORT_HW_RFC_2819_STATS_LEN ; 
 int MLXSW_SP_PORT_HW_RFC_2863_STATS_LEN ; 
 int MLXSW_SP_PORT_HW_RFC_3635_STATS_LEN ; 
 int MLXSW_SP_PORT_HW_STATS_LEN ; 
 int TC_MAX_QUEUE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_port_get_prio_strings (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  mlxsw_sp_port_get_tc_strings (int /*<<< orphan*/ **,int) ; 
 TYPE_7__* mlxsw_sp_port_hw_discard_stats ; 
 TYPE_6__* mlxsw_sp_port_hw_rfc_2819_stats ; 
 TYPE_5__* mlxsw_sp_port_hw_rfc_2863_stats ; 
 TYPE_4__* mlxsw_sp_port_hw_rfc_3635_stats ; 
 TYPE_3__* mlxsw_sp_port_hw_stats ; 
 struct mlxsw_sp_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void mlxsw_sp_port_get_strings(struct net_device *dev,
				      u32 stringset, u8 *data)
{
	struct mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	u8 *p = data;
	int i;

	switch (stringset) {
	case ETH_SS_STATS:
		for (i = 0; i < MLXSW_SP_PORT_HW_STATS_LEN; i++) {
			memcpy(p, mlxsw_sp_port_hw_stats[i].str,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		}

		for (i = 0; i < MLXSW_SP_PORT_HW_RFC_2863_STATS_LEN; i++) {
			memcpy(p, mlxsw_sp_port_hw_rfc_2863_stats[i].str,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		}

		for (i = 0; i < MLXSW_SP_PORT_HW_RFC_2819_STATS_LEN; i++) {
			memcpy(p, mlxsw_sp_port_hw_rfc_2819_stats[i].str,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		}

		for (i = 0; i < MLXSW_SP_PORT_HW_RFC_3635_STATS_LEN; i++) {
			memcpy(p, mlxsw_sp_port_hw_rfc_3635_stats[i].str,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		}

		for (i = 0; i < MLXSW_SP_PORT_HW_DISCARD_STATS_LEN; i++) {
			memcpy(p, mlxsw_sp_port_hw_discard_stats[i].str,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		}

		for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
			mlxsw_sp_port_get_prio_strings(&p, i);

		for (i = 0; i < TC_MAX_QUEUE; i++)
			mlxsw_sp_port_get_tc_strings(&p, i);

		mlxsw_sp_port->mlxsw_sp->ptp_ops->get_stats_strings(&p);
		break;
	}
}