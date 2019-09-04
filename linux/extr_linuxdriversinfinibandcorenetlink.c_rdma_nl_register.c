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
struct TYPE_2__ {struct rdma_nl_cbs const* cb_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,unsigned int) ; 
 int /*<<< orphan*/  is_nl_msg_valid (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_nl_mutex ; 
 TYPE_1__* rdma_nl_types ; 

void rdma_nl_register(unsigned int index,
		      const struct rdma_nl_cbs cb_table[])
{
	mutex_lock(&rdma_nl_mutex);
	if (!is_nl_msg_valid(index, 0)) {
		/*
		 * All clients are not interesting in success/failure of
		 * this call. They want to see the print to error log and
		 * continue their initialization. Print warning for them,
		 * because it is programmer's error to be here.
		 */
		mutex_unlock(&rdma_nl_mutex);
		WARN(true,
		     "The not-valid %u index was supplied to RDMA netlink\n",
		     index);
		return;
	}

	if (rdma_nl_types[index].cb_table) {
		mutex_unlock(&rdma_nl_mutex);
		WARN(true,
		     "The %u index is already registered in RDMA netlink\n",
		     index);
		return;
	}

	rdma_nl_types[index].cb_table = cb_table;
	mutex_unlock(&rdma_nl_mutex);
}