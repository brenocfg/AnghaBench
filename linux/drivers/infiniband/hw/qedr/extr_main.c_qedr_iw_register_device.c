#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  iw_ifname; int /*<<< orphan*/  node_type; } ;
struct qedr_dev {TYPE_1__* ndev; TYPE_2__ ibdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDMA_NODE_RNIC ; 
 int /*<<< orphan*/  ib_set_device_ops (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qedr_iw_dev_ops ; 

__attribute__((used)) static int qedr_iw_register_device(struct qedr_dev *dev)
{
	dev->ibdev.node_type = RDMA_NODE_RNIC;

	ib_set_device_ops(&dev->ibdev, &qedr_iw_dev_ops);

	memcpy(dev->ibdev.iw_ifname,
	       dev->ndev->name, sizeof(dev->ibdev.iw_ifname));

	return 0;
}