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
struct TYPE_2__ {struct ib_gid_attr const* sgid_attr; } ;
struct rdma_ah_attr {TYPE_1__ grh; } ;
struct ib_gid_attr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rdma_destroy_ah_attr (struct rdma_ah_attr*) ; 

__attribute__((used)) static void rdma_unfill_sgid_attr(struct rdma_ah_attr *ah_attr,
				  const struct ib_gid_attr *old_sgid_attr)
{
	/*
	 * Fill didn't change anything, the caller retains ownership of
	 * whatever it passed
	 */
	if (ah_attr->grh.sgid_attr == old_sgid_attr)
		return;

	/*
	 * Otherwise, we need to undo what rdma_fill_sgid_attr so the caller
	 * doesn't see any change in the rdma_ah_attr. If we get here
	 * old_sgid_attr is NULL.
	 */
	rdma_destroy_ah_attr(ah_attr);
}