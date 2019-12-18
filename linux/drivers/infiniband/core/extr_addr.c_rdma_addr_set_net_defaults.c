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
struct rdma_dev_addr {scalar_t__ bound_dev_if; int /*<<< orphan*/ * net; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_net ; 

__attribute__((used)) static void rdma_addr_set_net_defaults(struct rdma_dev_addr *addr)
{
	addr->net = &init_net;
	addr->bound_dev_if = 0;
}