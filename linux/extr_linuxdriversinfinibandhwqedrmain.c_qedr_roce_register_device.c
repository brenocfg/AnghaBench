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
struct TYPE_2__ {int /*<<< orphan*/  get_port_immutable; int /*<<< orphan*/  node_type; } ;
struct qedr_dev {TYPE_1__ ibdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDMA_NODE_IB_CA ; 
 int /*<<< orphan*/  qedr_roce_port_immutable ; 

__attribute__((used)) static void qedr_roce_register_device(struct qedr_dev *dev)
{
	dev->ibdev.node_type = RDMA_NODE_IB_CA;

	dev->ibdev.get_port_immutable = qedr_roce_port_immutable;
}