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
typedef  int /*<<< orphan*/  u64 ;
struct ocrdma_tx_stats {scalar_t__ ack_timeouts; int /*<<< orphan*/  read_rsp_bytes_hi; int /*<<< orphan*/  read_rsp_bytes_lo; int /*<<< orphan*/  read_req_bytes_hi; int /*<<< orphan*/  read_req_bytes_lo; int /*<<< orphan*/  write_bytes_hi; int /*<<< orphan*/  write_bytes_lo; int /*<<< orphan*/  send_bytes_hi; int /*<<< orphan*/  send_bytes_lo; int /*<<< orphan*/  ack_pkts_hi; int /*<<< orphan*/  ack_pkts_lo; int /*<<< orphan*/  read_rsp_pkts_hi; int /*<<< orphan*/  read_rsp_pkts_lo; int /*<<< orphan*/  read_pkts_hi; int /*<<< orphan*/  read_pkts_lo; int /*<<< orphan*/  write_pkts_hi; int /*<<< orphan*/  write_pkts_lo; int /*<<< orphan*/  send_pkts_hi; int /*<<< orphan*/  send_pkts_lo; } ;
struct ocrdma_rdma_stats_resp {struct ocrdma_tx_stats tx_stats; } ;
struct TYPE_2__ {char* debugfs_mem; scalar_t__ va; } ;
struct ocrdma_dev {TYPE_1__ stats_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCRDMA_MAX_DBGFS_MEM ; 
 int /*<<< orphan*/  convert_to_64bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocrdma_add_stat (char*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *ocrdma_tx_stats(struct ocrdma_dev *dev)
{
	char *stats = dev->stats_mem.debugfs_mem, *pcur;
	struct ocrdma_rdma_stats_resp *rdma_stats =
		(struct ocrdma_rdma_stats_resp *)dev->stats_mem.va;
	struct ocrdma_tx_stats *tx_stats = &rdma_stats->tx_stats;

	memset(stats, 0, (OCRDMA_MAX_DBGFS_MEM));

	pcur = stats;
	pcur += ocrdma_add_stat(stats, pcur, "send_pkts",
				convert_to_64bit(tx_stats->send_pkts_lo,
						 tx_stats->send_pkts_hi));
	pcur += ocrdma_add_stat(stats, pcur, "write_pkts",
				convert_to_64bit(tx_stats->write_pkts_lo,
						 tx_stats->write_pkts_hi));
	pcur += ocrdma_add_stat(stats, pcur, "read_pkts",
				convert_to_64bit(tx_stats->read_pkts_lo,
						 tx_stats->read_pkts_hi));
	pcur += ocrdma_add_stat(stats, pcur, "read_rsp_pkts",
				convert_to_64bit(tx_stats->read_rsp_pkts_lo,
						 tx_stats->read_rsp_pkts_hi));
	pcur += ocrdma_add_stat(stats, pcur, "ack_pkts",
				convert_to_64bit(tx_stats->ack_pkts_lo,
						 tx_stats->ack_pkts_hi));
	pcur += ocrdma_add_stat(stats, pcur, "send_bytes",
				convert_to_64bit(tx_stats->send_bytes_lo,
						 tx_stats->send_bytes_hi));
	pcur += ocrdma_add_stat(stats, pcur, "write_bytes",
				convert_to_64bit(tx_stats->write_bytes_lo,
						 tx_stats->write_bytes_hi));
	pcur += ocrdma_add_stat(stats, pcur, "read_req_bytes",
				convert_to_64bit(tx_stats->read_req_bytes_lo,
						 tx_stats->read_req_bytes_hi));
	pcur += ocrdma_add_stat(stats, pcur, "read_rsp_bytes",
				convert_to_64bit(tx_stats->read_rsp_bytes_lo,
						 tx_stats->read_rsp_bytes_hi));
	pcur += ocrdma_add_stat(stats, pcur, "ack_timeouts",
				(u64)tx_stats->ack_timeouts);

	return stats;
}