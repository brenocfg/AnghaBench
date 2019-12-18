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
struct rhashtable_iter {int dummy; } ;
struct bnxt_tc_stats_batch {void* flow_node; } ;
struct bnxt_tc_info {struct rhashtable_iter iter; } ;
struct bnxt {struct bnxt_tc_info* tc_info; } ;

/* Variables and functions */
 int BNXT_FLOW_STATS_BATCH_MAX ; 
 int EAGAIN ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 void* rhashtable_walk_next (struct rhashtable_iter*) ; 
 int /*<<< orphan*/  rhashtable_walk_start (struct rhashtable_iter*) ; 
 int /*<<< orphan*/  rhashtable_walk_stop (struct rhashtable_iter*) ; 

__attribute__((used)) static int
bnxt_tc_flow_stats_batch_prep(struct bnxt *bp,
			      struct bnxt_tc_stats_batch stats_batch[],
			      int *num_flows)
{
	struct bnxt_tc_info *tc_info = bp->tc_info;
	struct rhashtable_iter *iter = &tc_info->iter;
	void *flow_node;
	int rc, i;

	rhashtable_walk_start(iter);

	rc = 0;
	for (i = 0; i < BNXT_FLOW_STATS_BATCH_MAX; i++) {
		flow_node = rhashtable_walk_next(iter);
		if (IS_ERR(flow_node)) {
			i = 0;
			if (PTR_ERR(flow_node) == -EAGAIN) {
				continue;
			} else {
				rc = PTR_ERR(flow_node);
				goto done;
			}
		}

		/* No more flows */
		if (!flow_node)
			goto done;

		stats_batch[i].flow_node = flow_node;
	}
done:
	rhashtable_walk_stop(iter);
	*num_flows = i;
	return rc;
}