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
struct mlxsw_sp_port_hw_stats {int dummy; } ;
typedef  enum mlxsw_reg_ppcnt_grp { ____Placeholder_mlxsw_reg_ppcnt_grp } mlxsw_reg_ppcnt_grp ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  MLXSW_REG_PPCNT_DISCARD_CNT 134 
#define  MLXSW_REG_PPCNT_IEEE_8023_CNT 133 
#define  MLXSW_REG_PPCNT_PRIO_CNT 132 
#define  MLXSW_REG_PPCNT_RFC_2819_CNT 131 
#define  MLXSW_REG_PPCNT_RFC_2863_CNT 130 
#define  MLXSW_REG_PPCNT_RFC_3635_CNT 129 
#define  MLXSW_REG_PPCNT_TC_CNT 128 
 int MLXSW_SP_PORT_HW_DISCARD_STATS_LEN ; 
 int MLXSW_SP_PORT_HW_PRIO_STATS_LEN ; 
 int MLXSW_SP_PORT_HW_RFC_2819_STATS_LEN ; 
 int MLXSW_SP_PORT_HW_RFC_2863_STATS_LEN ; 
 int MLXSW_SP_PORT_HW_RFC_3635_STATS_LEN ; 
 int MLXSW_SP_PORT_HW_STATS_LEN ; 
 int MLXSW_SP_PORT_HW_TC_STATS_LEN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct mlxsw_sp_port_hw_stats* mlxsw_sp_port_hw_discard_stats ; 
 struct mlxsw_sp_port_hw_stats* mlxsw_sp_port_hw_prio_stats ; 
 struct mlxsw_sp_port_hw_stats* mlxsw_sp_port_hw_rfc_2819_stats ; 
 struct mlxsw_sp_port_hw_stats* mlxsw_sp_port_hw_rfc_2863_stats ; 
 struct mlxsw_sp_port_hw_stats* mlxsw_sp_port_hw_rfc_3635_stats ; 
 struct mlxsw_sp_port_hw_stats* mlxsw_sp_port_hw_stats ; 
 struct mlxsw_sp_port_hw_stats* mlxsw_sp_port_hw_tc_stats ; 

__attribute__((used)) static int
mlxsw_sp_get_hw_stats_by_group(struct mlxsw_sp_port_hw_stats **p_hw_stats,
			       int *p_len, enum mlxsw_reg_ppcnt_grp grp)
{
	switch (grp) {
	case MLXSW_REG_PPCNT_IEEE_8023_CNT:
		*p_hw_stats = mlxsw_sp_port_hw_stats;
		*p_len = MLXSW_SP_PORT_HW_STATS_LEN;
		break;
	case MLXSW_REG_PPCNT_RFC_2863_CNT:
		*p_hw_stats = mlxsw_sp_port_hw_rfc_2863_stats;
		*p_len = MLXSW_SP_PORT_HW_RFC_2863_STATS_LEN;
		break;
	case MLXSW_REG_PPCNT_RFC_2819_CNT:
		*p_hw_stats = mlxsw_sp_port_hw_rfc_2819_stats;
		*p_len = MLXSW_SP_PORT_HW_RFC_2819_STATS_LEN;
		break;
	case MLXSW_REG_PPCNT_RFC_3635_CNT:
		*p_hw_stats = mlxsw_sp_port_hw_rfc_3635_stats;
		*p_len = MLXSW_SP_PORT_HW_RFC_3635_STATS_LEN;
		break;
	case MLXSW_REG_PPCNT_DISCARD_CNT:
		*p_hw_stats = mlxsw_sp_port_hw_discard_stats;
		*p_len = MLXSW_SP_PORT_HW_DISCARD_STATS_LEN;
		break;
	case MLXSW_REG_PPCNT_PRIO_CNT:
		*p_hw_stats = mlxsw_sp_port_hw_prio_stats;
		*p_len = MLXSW_SP_PORT_HW_PRIO_STATS_LEN;
		break;
	case MLXSW_REG_PPCNT_TC_CNT:
		*p_hw_stats = mlxsw_sp_port_hw_tc_stats;
		*p_len = MLXSW_SP_PORT_HW_TC_STATS_LEN;
		break;
	default:
		WARN_ON(1);
		return -EOPNOTSUPP;
	}
	return 0;
}