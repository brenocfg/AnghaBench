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
struct TYPE_4__ {int /*<<< orphan*/ * ring; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ring; } ;
struct tbnet {TYPE_2__ tx_ring; TYPE_1__ rx_ring; int /*<<< orphan*/  disconnect_work; int /*<<< orphan*/  napi; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct tbnet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  tb_ring_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tbnet_tear_down (struct tbnet*,int) ; 

__attribute__((used)) static int tbnet_stop(struct net_device *dev)
{
	struct tbnet *net = netdev_priv(dev);

	napi_disable(&net->napi);

	cancel_work_sync(&net->disconnect_work);
	tbnet_tear_down(net, true);

	tb_ring_free(net->rx_ring.ring);
	net->rx_ring.ring = NULL;
	tb_ring_free(net->tx_ring.ring);
	net->tx_ring.ring = NULL;

	return 0;
}