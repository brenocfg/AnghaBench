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
struct ionic_lif {int /*<<< orphan*/  state; int /*<<< orphan*/  nxqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  IONIC_LIF_UP ; 
 int /*<<< orphan*/  ionic_link_status_check_request (struct ionic_lif*) ; 
 int ionic_txrx_alloc (struct ionic_lif*) ; 
 int /*<<< orphan*/  ionic_txrx_deinit (struct ionic_lif*) ; 
 int ionic_txrx_enable (struct ionic_lif*) ; 
 int /*<<< orphan*/  ionic_txrx_free (struct ionic_lif*) ; 
 int ionic_txrx_init (struct ionic_lif*) ; 
 struct ionic_lif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_set_real_num_rx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_set_real_num_tx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ionic_open(struct net_device *netdev)
{
	struct ionic_lif *lif = netdev_priv(netdev);
	int err;

	netif_carrier_off(netdev);

	err = ionic_txrx_alloc(lif);
	if (err)
		return err;

	err = ionic_txrx_init(lif);
	if (err)
		goto err_txrx_free;

	err = ionic_txrx_enable(lif);
	if (err)
		goto err_txrx_deinit;

	netif_set_real_num_tx_queues(netdev, lif->nxqs);
	netif_set_real_num_rx_queues(netdev, lif->nxqs);

	set_bit(IONIC_LIF_UP, lif->state);

	ionic_link_status_check_request(lif);
	if (netif_carrier_ok(netdev))
		netif_tx_wake_all_queues(netdev);

	return 0;

err_txrx_deinit:
	ionic_txrx_deinit(lif);
err_txrx_free:
	ionic_txrx_free(lif);
	return err;
}