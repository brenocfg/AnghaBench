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
struct TYPE_2__ {int /*<<< orphan*/  nelems; } ;
struct bnxt_tc_info {int /*<<< orphan*/  iter; int /*<<< orphan*/  stats_batch; TYPE_1__ flow_table; } ;
struct bnxt {struct bnxt_tc_info* tc_info; } ;

/* Variables and functions */
 int EAGAIN ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int bnxt_tc_flow_stats_batch_prep (struct bnxt*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bnxt_tc_flow_stats_batch_update (struct bnxt*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhashtable_walk_enter (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rhashtable_walk_exit (int /*<<< orphan*/ *) ; 

void bnxt_tc_flow_stats_work(struct bnxt *bp)
{
	struct bnxt_tc_info *tc_info = bp->tc_info;
	int num_flows, rc;

	num_flows = atomic_read(&tc_info->flow_table.nelems);
	if (!num_flows)
		return;

	rhashtable_walk_enter(&tc_info->flow_table, &tc_info->iter);

	for (;;) {
		rc = bnxt_tc_flow_stats_batch_prep(bp, tc_info->stats_batch,
						   &num_flows);
		if (rc) {
			if (rc == -EAGAIN)
				continue;
			break;
		}

		if (!num_flows)
			break;

		bnxt_tc_flow_stats_batch_update(bp, num_flows,
						tc_info->stats_batch);
	}

	rhashtable_walk_exit(&tc_info->iter);
}