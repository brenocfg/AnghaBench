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
struct rdma_nl_cbs {int /*<<< orphan*/  doit; int /*<<< orphan*/  dump; } ;
struct TYPE_2__ {struct rdma_nl_cbs* cb_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_nl_msg_valid (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_nl_mutex ; 
 TYPE_1__* rdma_nl_types ; 
 int /*<<< orphan*/  request_module (char*,unsigned int) ; 

__attribute__((used)) static bool is_nl_valid(unsigned int type, unsigned int op)
{
	const struct rdma_nl_cbs *cb_table;

	if (!is_nl_msg_valid(type, op))
		return false;

	if (!rdma_nl_types[type].cb_table) {
		mutex_unlock(&rdma_nl_mutex);
		request_module("rdma-netlink-subsys-%d", type);
		mutex_lock(&rdma_nl_mutex);
	}

	cb_table = rdma_nl_types[type].cb_table;

	if (!cb_table || (!cb_table[op].dump && !cb_table[op].doit))
		return false;
	return true;
}