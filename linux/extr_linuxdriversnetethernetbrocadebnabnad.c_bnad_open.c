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
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  enet; } ;
struct bnad {int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  bna_lock; TYPE_2__ bna; TYPE_1__* netdev; } ;
struct bna_pause_config {scalar_t__ rx_pause; scalar_t__ tx_pause; } ;
struct TYPE_3__ {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNAD_FRAME_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bna_enet_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bna_enet_mtu_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bna_enet_pause_config (int /*<<< orphan*/ *,struct bna_pause_config*) ; 
 int /*<<< orphan*/  bnad_destroy_tx (struct bnad*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnad_enable_default_bcast (struct bnad*) ; 
 int /*<<< orphan*/  bnad_mac_addr_set_locked (struct bnad*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnad_restore_vlans (struct bnad*,int /*<<< orphan*/ ) ; 
 int bnad_setup_rx (struct bnad*,int /*<<< orphan*/ ) ; 
 int bnad_setup_tx (struct bnad*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnad_stats_timer_start (struct bnad*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct bnad* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
bnad_open(struct net_device *netdev)
{
	int err;
	struct bnad *bnad = netdev_priv(netdev);
	struct bna_pause_config pause_config;
	unsigned long flags;

	mutex_lock(&bnad->conf_mutex);

	/* Tx */
	err = bnad_setup_tx(bnad, 0);
	if (err)
		goto err_return;

	/* Rx */
	err = bnad_setup_rx(bnad, 0);
	if (err)
		goto cleanup_tx;

	/* Port */
	pause_config.tx_pause = 0;
	pause_config.rx_pause = 0;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_enet_mtu_set(&bnad->bna.enet,
			 BNAD_FRAME_SIZE(bnad->netdev->mtu), NULL);
	bna_enet_pause_config(&bnad->bna.enet, &pause_config);
	bna_enet_enable(&bnad->bna.enet);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	/* Enable broadcast */
	bnad_enable_default_bcast(bnad);

	/* Restore VLANs, if any */
	bnad_restore_vlans(bnad, 0);

	/* Set the UCAST address */
	spin_lock_irqsave(&bnad->bna_lock, flags);
	bnad_mac_addr_set_locked(bnad, netdev->dev_addr);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	/* Start the stats timer */
	bnad_stats_timer_start(bnad);

	mutex_unlock(&bnad->conf_mutex);

	return 0;

cleanup_tx:
	bnad_destroy_tx(bnad, 0);

err_return:
	mutex_unlock(&bnad->conf_mutex);
	return err;
}