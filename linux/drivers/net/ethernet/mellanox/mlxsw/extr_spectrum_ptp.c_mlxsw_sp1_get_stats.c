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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {int /*<<< orphan*/  stats; } ;
struct mlxsw_sp_port {TYPE_1__ ptp; } ;
typedef  int /*<<< orphan*/  ptrdiff_t ;
struct TYPE_4__ {int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int MLXSW_SP_PTP_PORT_STATS_LEN ; 
 TYPE_2__* mlxsw_sp_ptp_port_stats ; 

void mlxsw_sp1_get_stats(struct mlxsw_sp_port *mlxsw_sp_port,
			 u64 *data, int data_index)
{
	void *stats = &mlxsw_sp_port->ptp.stats;
	ptrdiff_t offset;
	int i;

	data += data_index;
	for (i = 0; i < MLXSW_SP_PTP_PORT_STATS_LEN; i++) {
		offset = mlxsw_sp_ptp_port_stats[i].offset;
		*data++ = *(u64 *)(stats + offset);
	}
}