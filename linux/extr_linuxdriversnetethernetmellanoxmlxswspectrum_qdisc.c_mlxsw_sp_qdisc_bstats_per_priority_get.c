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
typedef  scalar_t__ u64 ;
struct mlxsw_sp_port_xstats {scalar_t__* tx_bytes; scalar_t__* tx_packets; } ;

/* Variables and functions */
 int BIT (int) ; 
 int IEEE_8021QAZ_MAX_TCS ; 

__attribute__((used)) static void
mlxsw_sp_qdisc_bstats_per_priority_get(struct mlxsw_sp_port_xstats *xstats,
				       u8 prio_bitmap, u64 *tx_packets,
				       u64 *tx_bytes)
{
	int i;

	*tx_packets = 0;
	*tx_bytes = 0;
	for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		if (prio_bitmap & BIT(i)) {
			*tx_packets += xstats->tx_packets[i];
			*tx_bytes += xstats->tx_bytes[i];
		}
	}
}