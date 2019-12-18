#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  ch_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  ch_id; } ;
struct net_dev_context {TYPE_2__ tx; TYPE_3__* iface; TYPE_1__ rx; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* request_netinfo ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  comp ; 
 int /*<<< orphan*/  most_stop_channel (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct net_dev_context* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int most_nd_stop(struct net_device *dev)
{
	struct net_dev_context *nd = netdev_priv(dev);

	netif_stop_queue(dev);
	if (nd->iface->request_netinfo)
		nd->iface->request_netinfo(nd->iface, nd->tx.ch_id, NULL);
	most_stop_channel(nd->iface, nd->rx.ch_id, &comp);
	most_stop_channel(nd->iface, nd->tx.ch_id, &comp);

	return 0;
}