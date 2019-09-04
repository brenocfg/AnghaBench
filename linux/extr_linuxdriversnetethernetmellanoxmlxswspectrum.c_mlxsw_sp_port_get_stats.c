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
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 int IEEE_8021QAZ_MAX_TCS ; 
 int /*<<< orphan*/  MLXSW_REG_PPCNT_IEEE_8023_CNT ; 
 int /*<<< orphan*/  MLXSW_REG_PPCNT_PRIO_CNT ; 
 int /*<<< orphan*/  MLXSW_REG_PPCNT_RFC_2819_CNT ; 
 int /*<<< orphan*/  MLXSW_REG_PPCNT_TC_CNT ; 
 scalar_t__ MLXSW_SP_PORT_HW_PRIO_STATS_LEN ; 
 scalar_t__ MLXSW_SP_PORT_HW_RFC_2819_STATS_LEN ; 
 int MLXSW_SP_PORT_HW_STATS_LEN ; 
 scalar_t__ MLXSW_SP_PORT_HW_TC_STATS_LEN ; 
 int TC_MAX_QUEUE ; 
 int /*<<< orphan*/  __mlxsw_sp_port_get_stats (struct net_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void mlxsw_sp_port_get_stats(struct net_device *dev,
				    struct ethtool_stats *stats, u64 *data)
{
	int i, data_index = 0;

	/* IEEE 802.3 Counters */
	__mlxsw_sp_port_get_stats(dev, MLXSW_REG_PPCNT_IEEE_8023_CNT, 0,
				  data, data_index);
	data_index = MLXSW_SP_PORT_HW_STATS_LEN;

	/* RFC 2819 Counters */
	__mlxsw_sp_port_get_stats(dev, MLXSW_REG_PPCNT_RFC_2819_CNT, 0,
				  data, data_index);
	data_index += MLXSW_SP_PORT_HW_RFC_2819_STATS_LEN;

	/* Per-Priority Counters */
	for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		__mlxsw_sp_port_get_stats(dev, MLXSW_REG_PPCNT_PRIO_CNT, i,
					  data, data_index);
		data_index += MLXSW_SP_PORT_HW_PRIO_STATS_LEN;
	}

	/* Per-TC Counters */
	for (i = 0; i < TC_MAX_QUEUE; i++) {
		__mlxsw_sp_port_get_stats(dev, MLXSW_REG_PPCNT_TC_CNT, i,
					  data, data_index);
		data_index += MLXSW_SP_PORT_HW_TC_STATS_LEN;
	}
}