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
struct net_device {int dummy; } ;
struct cfv_info {int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  vq_tx; int /*<<< orphan*/  napi; int /*<<< orphan*/  vr_rx; } ;
struct buf_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfv_destroy_genpool (struct cfv_info*) ; 
 int /*<<< orphan*/  cfv_release_used_buf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_buf_info (struct cfv_info*,struct buf_info*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct cfv_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct buf_info* virtqueue_detach_unused_buf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_disable_cb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vringh_notify_disable_kern (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cfv_netdev_close(struct net_device *netdev)
{
	struct cfv_info *cfv = netdev_priv(netdev);
	unsigned long flags;
	struct buf_info *buf_info;

	/* Disable interrupts, queues and NAPI polling */
	netif_carrier_off(netdev);
	virtqueue_disable_cb(cfv->vq_tx);
	vringh_notify_disable_kern(cfv->vr_rx);
	napi_disable(&cfv->napi);

	/* Release any TX buffers on both used and avilable rings */
	cfv_release_used_buf(cfv->vq_tx);
	spin_lock_irqsave(&cfv->tx_lock, flags);
	while ((buf_info = virtqueue_detach_unused_buf(cfv->vq_tx)))
		free_buf_info(cfv, buf_info);
	spin_unlock_irqrestore(&cfv->tx_lock, flags);

	/* Release all dma allocated memory and destroy the pool */
	cfv_destroy_genpool(cfv);
	return 0;
}