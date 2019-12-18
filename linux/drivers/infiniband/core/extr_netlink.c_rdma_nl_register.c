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
struct rdma_nl_cbs {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cb_table; } ;

/* Variables and functions */
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  is_nl_msg_valid (unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_1__* rdma_nl_types ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,struct rdma_nl_cbs const*) ; 

void rdma_nl_register(unsigned int index,
		      const struct rdma_nl_cbs cb_table[])
{
	if (WARN_ON(!is_nl_msg_valid(index, 0)) ||
	    WARN_ON(READ_ONCE(rdma_nl_types[index].cb_table)))
		return;

	/* Pairs with the READ_ONCE in is_nl_valid() */
	smp_store_release(&rdma_nl_types[index].cb_table, cb_table);
}