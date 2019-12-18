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
struct virtnet_info {int max_queue_pairs; TYPE_1__* sq; TYPE_2__* rq; int /*<<< orphan*/  refill; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  napi; int /*<<< orphan*/  xdp_rxq; } ;
struct TYPE_3__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct virtnet_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  virtnet_napi_tx_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdp_rxq_info_unreg (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int virtnet_close(struct net_device *dev)
{
	struct virtnet_info *vi = netdev_priv(dev);
	int i;

	/* Make sure refill_work doesn't re-enable napi! */
	cancel_delayed_work_sync(&vi->refill);

	for (i = 0; i < vi->max_queue_pairs; i++) {
		xdp_rxq_info_unreg(&vi->rq[i].xdp_rxq);
		napi_disable(&vi->rq[i].napi);
		virtnet_napi_tx_disable(&vi->sq[i].napi);
	}

	return 0;
}