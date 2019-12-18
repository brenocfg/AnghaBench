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
struct ocrdma_db_err_stats {scalar_t__ cq_overflow_errors; scalar_t__ rq_srq_doorbell_errors; scalar_t__ cq_doorbell_errors; scalar_t__ sq_doorbell_errors; } ;
struct ocrdma_rdma_stats_resp {struct ocrdma_db_err_stats db_err_stats; } ;
struct TYPE_2__ {char* debugfs_mem; scalar_t__ va; } ;
struct ocrdma_dev {TYPE_1__ stats_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCRDMA_MAX_DBGFS_MEM ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocrdma_add_stat (char*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *ocrdma_db_errstats(struct ocrdma_dev *dev)
{
	char *stats = dev->stats_mem.debugfs_mem, *pcur;
	struct ocrdma_rdma_stats_resp *rdma_stats =
		(struct ocrdma_rdma_stats_resp *)dev->stats_mem.va;
	struct ocrdma_db_err_stats *db_err_stats = &rdma_stats->db_err_stats;

	memset(stats, 0, (OCRDMA_MAX_DBGFS_MEM));

	pcur = stats;
	pcur += ocrdma_add_stat(stats, pcur, "sq_doorbell_errors",
				(u64)db_err_stats->sq_doorbell_errors);
	pcur += ocrdma_add_stat(stats, pcur, "cq_doorbell_errors",
				(u64)db_err_stats->cq_doorbell_errors);
	pcur += ocrdma_add_stat(stats, pcur, "rq_srq_doorbell_errors",
				(u64)db_err_stats->rq_srq_doorbell_errors);
	pcur += ocrdma_add_stat(stats, pcur, "cq_overflow_errors",
				(u64)db_err_stats->cq_overflow_errors);
	return stats;
}