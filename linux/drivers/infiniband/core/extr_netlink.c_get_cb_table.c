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
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct rdma_nl_cbs {int /*<<< orphan*/  doit; int /*<<< orphan*/  dump; } ;
struct TYPE_2__ {int /*<<< orphan*/  cb_table; int /*<<< orphan*/  sem; } ;

/* Variables and functions */
 unsigned int RDMA_NL_NLDEV ; 
 struct rdma_nl_cbs* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_net ; 
 TYPE_1__* rdma_nl_types ; 
 int /*<<< orphan*/  request_module (char*,unsigned int) ; 
 int /*<<< orphan*/ * sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const struct rdma_nl_cbs *
get_cb_table(const struct sk_buff *skb, unsigned int type, unsigned int op)
{
	const struct rdma_nl_cbs *cb_table;

	/*
	 * Currently only NLDEV client is supporting netlink commands in
	 * non init_net net namespace.
	 */
	if (sock_net(skb->sk) != &init_net && type != RDMA_NL_NLDEV)
		return NULL;

	cb_table = READ_ONCE(rdma_nl_types[type].cb_table);
	if (!cb_table) {
		/*
		 * Didn't get valid reference of the table, attempt module
		 * load once.
		 */
		up_read(&rdma_nl_types[type].sem);

		request_module("rdma-netlink-subsys-%d", type);

		down_read(&rdma_nl_types[type].sem);
		cb_table = READ_ONCE(rdma_nl_types[type].cb_table);
	}
	if (!cb_table || (!cb_table[op].dump && !cb_table[op].doit))
		return NULL;
	return cb_table;
}