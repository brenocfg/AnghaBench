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
struct tx_info {int /*<<< orphan*/  numq; } ;
struct rx_info {int dummy; } ;
struct velocity_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  mac_regs; int /*<<< orphan*/  napi; struct tx_info tx; struct rx_info rx; int /*<<< orphan*/  options; int /*<<< orphan*/  dev; int /*<<< orphan*/  pdev; struct net_device* netdev; } ;
struct net_device {int mtu; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VELOCITY_INIT_COLD ; 
 int /*<<< orphan*/  kfree (struct velocity_info*) ; 
 struct velocity_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_enable_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct velocity_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  velocity_free_rings (struct velocity_info*) ; 
 int /*<<< orphan*/  velocity_give_many_rx_descs (struct velocity_info*) ; 
 int /*<<< orphan*/  velocity_init_registers (struct velocity_info*,int /*<<< orphan*/ ) ; 
 int velocity_init_rings (struct velocity_info*,int) ; 
 int /*<<< orphan*/  velocity_shutdown (struct velocity_info*) ; 

__attribute__((used)) static int velocity_change_mtu(struct net_device *dev, int new_mtu)
{
	struct velocity_info *vptr = netdev_priv(dev);
	int ret = 0;

	if (!netif_running(dev)) {
		dev->mtu = new_mtu;
		goto out_0;
	}

	if (dev->mtu != new_mtu) {
		struct velocity_info *tmp_vptr;
		unsigned long flags;
		struct rx_info rx;
		struct tx_info tx;

		tmp_vptr = kzalloc(sizeof(*tmp_vptr), GFP_KERNEL);
		if (!tmp_vptr) {
			ret = -ENOMEM;
			goto out_0;
		}

		tmp_vptr->netdev = dev;
		tmp_vptr->pdev = vptr->pdev;
		tmp_vptr->dev = vptr->dev;
		tmp_vptr->options = vptr->options;
		tmp_vptr->tx.numq = vptr->tx.numq;

		ret = velocity_init_rings(tmp_vptr, new_mtu);
		if (ret < 0)
			goto out_free_tmp_vptr_1;

		napi_disable(&vptr->napi);

		spin_lock_irqsave(&vptr->lock, flags);

		netif_stop_queue(dev);
		velocity_shutdown(vptr);

		rx = vptr->rx;
		tx = vptr->tx;

		vptr->rx = tmp_vptr->rx;
		vptr->tx = tmp_vptr->tx;

		tmp_vptr->rx = rx;
		tmp_vptr->tx = tx;

		dev->mtu = new_mtu;

		velocity_init_registers(vptr, VELOCITY_INIT_COLD);

		velocity_give_many_rx_descs(vptr);

		napi_enable(&vptr->napi);

		mac_enable_int(vptr->mac_regs);
		netif_start_queue(dev);

		spin_unlock_irqrestore(&vptr->lock, flags);

		velocity_free_rings(tmp_vptr);

out_free_tmp_vptr_1:
		kfree(tmp_vptr);
	}
out_0:
	return ret;
}