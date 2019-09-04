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
struct mlx4_counter {int /*<<< orphan*/  rx_frames; int /*<<< orphan*/  tx_frames; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_bytes; } ;
struct ib_pma_portcounters_ext {int /*<<< orphan*/  port_rcv_packets; int /*<<< orphan*/  port_xmit_packets; void* port_rcv_data; void* port_xmit_data; } ;
struct ib_pma_portcounters {int /*<<< orphan*/  port_rcv_packets; int /*<<< orphan*/  port_xmit_packets; int /*<<< orphan*/  port_rcv_data; int /*<<< orphan*/  port_xmit_data; } ;
typedef  int __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ASSIGN_32BIT_COUNTER (int /*<<< orphan*/ ,int) ; 
#define  IB_PMA_PORT_COUNTERS 129 
#define  IB_PMA_PORT_COUNTERS_EXT 128 
 int be64_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be64 (int) ; 

__attribute__((used)) static void edit_counter(struct mlx4_counter *cnt, void *counters,
			 __be16 attr_id)
{
	switch (attr_id) {
	case IB_PMA_PORT_COUNTERS:
	{
		struct ib_pma_portcounters *pma_cnt =
			(struct ib_pma_portcounters *)counters;

		ASSIGN_32BIT_COUNTER(pma_cnt->port_xmit_data,
				     (be64_to_cpu(cnt->tx_bytes) >> 2));
		ASSIGN_32BIT_COUNTER(pma_cnt->port_rcv_data,
				     (be64_to_cpu(cnt->rx_bytes) >> 2));
		ASSIGN_32BIT_COUNTER(pma_cnt->port_xmit_packets,
				     be64_to_cpu(cnt->tx_frames));
		ASSIGN_32BIT_COUNTER(pma_cnt->port_rcv_packets,
				     be64_to_cpu(cnt->rx_frames));
		break;
	}
	case IB_PMA_PORT_COUNTERS_EXT:
	{
		struct ib_pma_portcounters_ext *pma_cnt_ext =
			(struct ib_pma_portcounters_ext *)counters;

		pma_cnt_ext->port_xmit_data =
			cpu_to_be64(be64_to_cpu(cnt->tx_bytes) >> 2);
		pma_cnt_ext->port_rcv_data =
			cpu_to_be64(be64_to_cpu(cnt->rx_bytes) >> 2);
		pma_cnt_ext->port_xmit_packets = cnt->tx_frames;
		pma_cnt_ext->port_rcv_packets = cnt->rx_frames;
		break;
	}
	}
}