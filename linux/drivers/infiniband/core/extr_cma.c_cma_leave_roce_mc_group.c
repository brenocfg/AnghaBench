#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct rdma_dev_addr {scalar_t__ bound_dev_if; int /*<<< orphan*/  net; } ;
struct TYPE_10__ {struct rdma_dev_addr dev_addr; } ;
struct TYPE_11__ {TYPE_4__ addr; } ;
struct TYPE_12__ {TYPE_5__ route; } ;
struct rdma_id_private {TYPE_6__ id; } ;
struct net_device {int dummy; } ;
struct TYPE_9__ {TYPE_2__* ib; } ;
struct cma_multicast {int /*<<< orphan*/  mcref; TYPE_3__ multicast; } ;
struct TYPE_7__ {int /*<<< orphan*/  mgid; } ;
struct TYPE_8__ {TYPE_1__ rec; } ;

/* Variables and functions */
 int /*<<< orphan*/  cma_igmp_send (struct net_device*,int /*<<< orphan*/ *,int) ; 
 struct net_device* dev_get_by_index (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mc ; 

__attribute__((used)) static void cma_leave_roce_mc_group(struct rdma_id_private *id_priv,
				    struct cma_multicast *mc)
{
	struct rdma_dev_addr *dev_addr = &id_priv->id.route.addr.dev_addr;
	struct net_device *ndev = NULL;

	if (dev_addr->bound_dev_if)
		ndev = dev_get_by_index(dev_addr->net, dev_addr->bound_dev_if);
	if (ndev) {
		cma_igmp_send(ndev, &mc->multicast.ib->rec.mgid, false);
		dev_put(ndev);
	}
	kref_put(&mc->mcref, release_mc);
}