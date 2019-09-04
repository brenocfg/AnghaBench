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
struct fm10k_intfc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fm10k_down (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_free_all_rx_resources (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_free_all_tx_resources (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_free_udp_port_info (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_qv_free_irq (struct fm10k_intfc*) ; 
 struct fm10k_intfc* netdev_priv (struct net_device*) ; 

int fm10k_close(struct net_device *netdev)
{
	struct fm10k_intfc *interface = netdev_priv(netdev);

	fm10k_down(interface);

	fm10k_qv_free_irq(interface);

	fm10k_free_udp_port_info(interface);

	fm10k_free_all_tx_resources(interface);
	fm10k_free_all_rx_resources(interface);

	return 0;
}