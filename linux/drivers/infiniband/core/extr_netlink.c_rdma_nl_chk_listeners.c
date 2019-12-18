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
struct rdma_dev_net {int /*<<< orphan*/  nl_sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_net ; 
 int netlink_has_listeners (int /*<<< orphan*/ ,unsigned int) ; 
 struct rdma_dev_net* rdma_net_to_dev_net (int /*<<< orphan*/ *) ; 

bool rdma_nl_chk_listeners(unsigned int group)
{
	struct rdma_dev_net *rnet = rdma_net_to_dev_net(&init_net);

	return netlink_has_listeners(rnet->nl_sock, group);
}