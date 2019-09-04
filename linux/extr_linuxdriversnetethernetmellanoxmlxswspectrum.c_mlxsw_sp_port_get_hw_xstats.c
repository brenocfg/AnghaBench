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
struct net_device {int dummy; } ;
struct mlxsw_sp_port_xstats {int /*<<< orphan*/ * tx_bytes; int /*<<< orphan*/ * tx_packets; int /*<<< orphan*/ * tail_drop; int /*<<< orphan*/ * backlog; int /*<<< orphan*/ * wred_drop; int /*<<< orphan*/  ecn; } ;

/* Variables and functions */
 int IEEE_8021QAZ_MAX_TCS ; 
 int /*<<< orphan*/  MLXSW_REG_PPCNT_EXT_CNT ; 
 int MLXSW_REG_PPCNT_LEN ; 
 int /*<<< orphan*/  MLXSW_REG_PPCNT_PRIO_CNT ; 
 int /*<<< orphan*/  MLXSW_REG_PPCNT_TC_CNT ; 
 int /*<<< orphan*/  MLXSW_REG_PPCNT_TC_CONG_TC ; 
 int TC_MAX_QUEUE ; 
 int /*<<< orphan*/  mlxsw_reg_ppcnt_ecn_marked_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ppcnt_tc_no_buffer_discard_uc_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ppcnt_tc_transmit_queue_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ppcnt_tx_frames_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ppcnt_tx_octets_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ppcnt_wred_discard_get (char*) ; 
 int mlxsw_sp_port_get_stats_raw (struct net_device*,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static void
mlxsw_sp_port_get_hw_xstats(struct net_device *dev,
			    struct mlxsw_sp_port_xstats *xstats)
{
	char ppcnt_pl[MLXSW_REG_PPCNT_LEN];
	int err, i;

	err = mlxsw_sp_port_get_stats_raw(dev, MLXSW_REG_PPCNT_EXT_CNT, 0,
					  ppcnt_pl);
	if (!err)
		xstats->ecn = mlxsw_reg_ppcnt_ecn_marked_get(ppcnt_pl);

	for (i = 0; i < TC_MAX_QUEUE; i++) {
		err = mlxsw_sp_port_get_stats_raw(dev,
						  MLXSW_REG_PPCNT_TC_CONG_TC,
						  i, ppcnt_pl);
		if (!err)
			xstats->wred_drop[i] =
				mlxsw_reg_ppcnt_wred_discard_get(ppcnt_pl);

		err = mlxsw_sp_port_get_stats_raw(dev, MLXSW_REG_PPCNT_TC_CNT,
						  i, ppcnt_pl);
		if (err)
			continue;

		xstats->backlog[i] =
			mlxsw_reg_ppcnt_tc_transmit_queue_get(ppcnt_pl);
		xstats->tail_drop[i] =
			mlxsw_reg_ppcnt_tc_no_buffer_discard_uc_get(ppcnt_pl);
	}

	for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		err = mlxsw_sp_port_get_stats_raw(dev, MLXSW_REG_PPCNT_PRIO_CNT,
						  i, ppcnt_pl);
		if (err)
			continue;

		xstats->tx_packets[i] = mlxsw_reg_ppcnt_tx_frames_get(ppcnt_pl);
		xstats->tx_bytes[i] = mlxsw_reg_ppcnt_tx_octets_get(ppcnt_pl);
	}
}