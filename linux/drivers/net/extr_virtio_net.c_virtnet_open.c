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
struct virtnet_info {int max_queue_pairs; int curr_queue_pairs; TYPE_1__* sq; TYPE_2__* rq; int /*<<< orphan*/  refill; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  napi; int /*<<< orphan*/  vq; int /*<<< orphan*/  xdp_rxq; } ;
struct TYPE_3__ {int /*<<< orphan*/  napi; int /*<<< orphan*/  vq; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MEM_TYPE_PAGE_SHARED ; 
 struct virtnet_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_fill_recv (struct virtnet_info*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtnet_napi_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtnet_napi_tx_enable (struct virtnet_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int xdp_rxq_info_reg (int /*<<< orphan*/ *,struct net_device*,int) ; 
 int xdp_rxq_info_reg_mem_model (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdp_rxq_info_unreg (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int virtnet_open(struct net_device *dev)
{
	struct virtnet_info *vi = netdev_priv(dev);
	int i, err;

	for (i = 0; i < vi->max_queue_pairs; i++) {
		if (i < vi->curr_queue_pairs)
			/* Make sure we have some buffers: if oom use wq. */
			if (!try_fill_recv(vi, &vi->rq[i], GFP_KERNEL))
				schedule_delayed_work(&vi->refill, 0);

		err = xdp_rxq_info_reg(&vi->rq[i].xdp_rxq, dev, i);
		if (err < 0)
			return err;

		err = xdp_rxq_info_reg_mem_model(&vi->rq[i].xdp_rxq,
						 MEM_TYPE_PAGE_SHARED, NULL);
		if (err < 0) {
			xdp_rxq_info_unreg(&vi->rq[i].xdp_rxq);
			return err;
		}

		virtnet_napi_enable(vi->rq[i].vq, &vi->rq[i].napi);
		virtnet_napi_tx_enable(vi, vi->sq[i].vq, &vi->sq[i].napi);
	}

	return 0;
}