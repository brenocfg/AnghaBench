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
 int /*<<< orphan*/  netlink_kernel_release (int /*<<< orphan*/ ) ; 

void rdma_nl_net_exit(struct rdma_dev_net *rnet)
{
	netlink_kernel_release(rnet->nl_sock);
}