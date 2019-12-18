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
struct rdma_counter_mode {scalar_t__ mode; int mask; } ;
typedef  enum rdma_nl_counter_mode { ____Placeholder_rdma_nl_counter_mode } rdma_nl_counter_mode ;
typedef  enum rdma_nl_counter_mask { ____Placeholder_rdma_nl_counter_mask } rdma_nl_counter_mask ;

/* Variables and functions */
 int ALL_AUTO_MODE_MASKS ; 
 int EINVAL ; 
 int RDMA_COUNTER_MODE_AUTO ; 
 scalar_t__ RDMA_COUNTER_MODE_NONE ; 

__attribute__((used)) static int __counter_set_mode(struct rdma_counter_mode *curr,
			      enum rdma_nl_counter_mode new_mode,
			      enum rdma_nl_counter_mask new_mask)
{
	if ((new_mode == RDMA_COUNTER_MODE_AUTO) &&
	    ((new_mask & (~ALL_AUTO_MODE_MASKS)) ||
	     (curr->mode != RDMA_COUNTER_MODE_NONE)))
		return -EINVAL;

	curr->mode = new_mode;
	curr->mask = new_mask;
	return 0;
}