#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rdma_dev_addr {scalar_t__ bound_dev_if; int /*<<< orphan*/  src_dev_addr; int /*<<< orphan*/  net; } ;
struct TYPE_5__ {struct rdma_dev_addr dev_addr; } ;
struct TYPE_6__ {TYPE_1__ addr; } ;
struct TYPE_8__ {TYPE_2__ route; } ;
struct rdma_id_private {int /*<<< orphan*/  refcount; TYPE_4__ id; } ;
struct net_device {scalar_t__ ifindex; int /*<<< orphan*/  name; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  event; } ;
struct cma_ndev_work {int /*<<< orphan*/  work; TYPE_3__ event; struct rdma_id_private* id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDMA_CM_EVENT_ADDR_CHANGE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cma_ndev_work_handler ; 
 int /*<<< orphan*/  cma_wq ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 struct cma_ndev_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cma_netdev_change(struct net_device *ndev, struct rdma_id_private *id_priv)
{
	struct rdma_dev_addr *dev_addr;
	struct cma_ndev_work *work;

	dev_addr = &id_priv->id.route.addr.dev_addr;

	if ((dev_addr->bound_dev_if == ndev->ifindex) &&
	    (net_eq(dev_net(ndev), dev_addr->net)) &&
	    memcmp(dev_addr->src_dev_addr, ndev->dev_addr, ndev->addr_len)) {
		pr_info("RDMA CM addr change for ndev %s used by id %p\n",
			ndev->name, &id_priv->id);
		work = kzalloc(sizeof *work, GFP_KERNEL);
		if (!work)
			return -ENOMEM;

		INIT_WORK(&work->work, cma_ndev_work_handler);
		work->id = id_priv;
		work->event.event = RDMA_CM_EVENT_ADDR_CHANGE;
		atomic_inc(&id_priv->refcount);
		queue_work(cma_wq, &work->work);
	}

	return 0;
}