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
typedef  void* u32 ;
struct icc_path {size_t num_nodes; TYPE_1__* reqs; } ;
struct icc_node {int dummy; } ;
struct TYPE_2__ {void* peak_bw; void* avg_bw; struct icc_node* node; } ;

/* Variables and functions */
 int /*<<< orphan*/  aggregate_requests (struct icc_node*) ; 
 int apply_constraints (struct icc_path*) ; 
 int /*<<< orphan*/  icc_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

int icc_set_bw(struct icc_path *path, u32 avg_bw, u32 peak_bw)
{
	struct icc_node *node;
	u32 old_avg, old_peak;
	size_t i;
	int ret;

	if (!path || !path->num_nodes)
		return 0;

	mutex_lock(&icc_lock);

	old_avg = path->reqs[0].avg_bw;
	old_peak = path->reqs[0].peak_bw;

	for (i = 0; i < path->num_nodes; i++) {
		node = path->reqs[i].node;

		/* update the consumer request for this path */
		path->reqs[i].avg_bw = avg_bw;
		path->reqs[i].peak_bw = peak_bw;

		/* aggregate requests for this node */
		aggregate_requests(node);
	}

	ret = apply_constraints(path);
	if (ret) {
		pr_debug("interconnect: error applying constraints (%d)\n",
			 ret);

		for (i = 0; i < path->num_nodes; i++) {
			node = path->reqs[i].node;
			path->reqs[i].avg_bw = old_avg;
			path->reqs[i].peak_bw = old_peak;
			aggregate_requests(node);
		}
		apply_constraints(path);
	}

	mutex_unlock(&icc_lock);

	return ret;
}