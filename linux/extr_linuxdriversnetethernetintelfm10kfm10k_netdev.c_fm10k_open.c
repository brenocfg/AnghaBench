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
struct fm10k_intfc {int /*<<< orphan*/  num_rx_queues; int /*<<< orphan*/  num_tx_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  fm10k_free_all_rx_resources (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_free_all_tx_resources (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_qv_free_irq (struct fm10k_intfc*) ; 
 int fm10k_qv_request_irq (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_request_glort_range (struct fm10k_intfc*) ; 
 int fm10k_setup_all_rx_resources (struct fm10k_intfc*) ; 
 int fm10k_setup_all_tx_resources (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_up (struct fm10k_intfc*) ; 
 struct fm10k_intfc* netdev_priv (struct net_device*) ; 
 int netif_set_real_num_rx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int netif_set_real_num_tx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udp_tunnel_get_rx_info (struct net_device*) ; 

int fm10k_open(struct net_device *netdev)
{
	struct fm10k_intfc *interface = netdev_priv(netdev);
	int err;

	/* allocate transmit descriptors */
	err = fm10k_setup_all_tx_resources(interface);
	if (err)
		goto err_setup_tx;

	/* allocate receive descriptors */
	err = fm10k_setup_all_rx_resources(interface);
	if (err)
		goto err_setup_rx;

	/* allocate interrupt resources */
	err = fm10k_qv_request_irq(interface);
	if (err)
		goto err_req_irq;

	/* setup GLORT assignment for this port */
	fm10k_request_glort_range(interface);

	/* Notify the stack of the actual queue counts */
	err = netif_set_real_num_tx_queues(netdev,
					   interface->num_tx_queues);
	if (err)
		goto err_set_queues;

	err = netif_set_real_num_rx_queues(netdev,
					   interface->num_rx_queues);
	if (err)
		goto err_set_queues;

	udp_tunnel_get_rx_info(netdev);

	fm10k_up(interface);

	return 0;

err_set_queues:
	fm10k_qv_free_irq(interface);
err_req_irq:
	fm10k_free_all_rx_resources(interface);
err_setup_rx:
	fm10k_free_all_tx_resources(interface);
err_setup_tx:
	return err;
}