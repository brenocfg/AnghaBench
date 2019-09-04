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
typedef  scalar_t__ u64 ;
struct ocrdma_rx_stats {scalar_t__ roce_frame_payload_len_drops; scalar_t__ roce_frame_icrc_drops; int /*<<< orphan*/  roce_frames_hi; int /*<<< orphan*/  roce_frames_lo; } ;
struct ocrdma_rdma_stats_resp {struct ocrdma_rx_stats rx_stats; } ;
struct TYPE_2__ {scalar_t__ va; } ;
struct ocrdma_dev {TYPE_1__ stats_mem; } ;

/* Variables and functions */
 scalar_t__ convert_to_64bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 ocrdma_sysfs_rcv_pkts(struct ocrdma_dev *dev)
{
	struct ocrdma_rdma_stats_resp *rdma_stats =
		(struct ocrdma_rdma_stats_resp *)dev->stats_mem.va;
	struct ocrdma_rx_stats *rx_stats = &rdma_stats->rx_stats;

	return convert_to_64bit(rx_stats->roce_frames_lo,
		rx_stats->roce_frames_hi) + (u64)rx_stats->roce_frame_icrc_drops
		+ (u64)rx_stats->roce_frame_payload_len_drops;
}