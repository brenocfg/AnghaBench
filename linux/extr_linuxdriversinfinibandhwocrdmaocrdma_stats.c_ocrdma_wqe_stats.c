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
struct ocrdma_wqe_stats {scalar_t__ dpp_wqe_drops; int /*<<< orphan*/  invalidate_wqes_hi; int /*<<< orphan*/  invalidate_wqes_lo; int /*<<< orphan*/  mw_bind_wqes_hi; int /*<<< orphan*/  mw_bind_wqes_lo; int /*<<< orphan*/  frmr_wqes_hi; int /*<<< orphan*/  frmr_wqes_lo; int /*<<< orphan*/  read_wqes_hi; int /*<<< orphan*/  read_wqes_lo; int /*<<< orphan*/  large_write_rc_wqes_hi; int /*<<< orphan*/  large_write_rc_wqes_lo; int /*<<< orphan*/  large_send_rc_wqes_hi; int /*<<< orphan*/  large_send_rc_wqes_lo; } ;
struct ocrdma_rdma_stats_resp {struct ocrdma_wqe_stats wqe_stats; } ;
struct TYPE_2__ {char* debugfs_mem; scalar_t__ va; } ;
struct ocrdma_dev {TYPE_1__ stats_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCRDMA_MAX_DBGFS_MEM ; 
 int /*<<< orphan*/  convert_to_64bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocrdma_add_stat (char*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *ocrdma_wqe_stats(struct ocrdma_dev *dev)
{
	char *stats = dev->stats_mem.debugfs_mem, *pcur;
	struct ocrdma_rdma_stats_resp *rdma_stats =
		(struct ocrdma_rdma_stats_resp *)dev->stats_mem.va;
	struct ocrdma_wqe_stats	*wqe_stats = &rdma_stats->wqe_stats;

	memset(stats, 0, (OCRDMA_MAX_DBGFS_MEM));

	pcur = stats;
	pcur += ocrdma_add_stat(stats, pcur, "large_send_rc_wqes",
		convert_to_64bit(wqe_stats->large_send_rc_wqes_lo,
				 wqe_stats->large_send_rc_wqes_hi));
	pcur += ocrdma_add_stat(stats, pcur, "large_write_rc_wqes",
		convert_to_64bit(wqe_stats->large_write_rc_wqes_lo,
				 wqe_stats->large_write_rc_wqes_hi));
	pcur += ocrdma_add_stat(stats, pcur, "read_wqes",
				convert_to_64bit(wqe_stats->read_wqes_lo,
						 wqe_stats->read_wqes_hi));
	pcur += ocrdma_add_stat(stats, pcur, "frmr_wqes",
				convert_to_64bit(wqe_stats->frmr_wqes_lo,
						 wqe_stats->frmr_wqes_hi));
	pcur += ocrdma_add_stat(stats, pcur, "mw_bind_wqes",
				convert_to_64bit(wqe_stats->mw_bind_wqes_lo,
						 wqe_stats->mw_bind_wqes_hi));
	pcur += ocrdma_add_stat(stats, pcur, "invalidate_wqes",
		convert_to_64bit(wqe_stats->invalidate_wqes_lo,
				 wqe_stats->invalidate_wqes_hi));
	pcur += ocrdma_add_stat(stats, pcur, "dpp_wqe_drops",
				(u64)wqe_stats->dpp_wqe_drops);
	return stats;
}