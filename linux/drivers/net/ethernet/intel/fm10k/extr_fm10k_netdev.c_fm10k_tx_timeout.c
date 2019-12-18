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
struct net_device {int watchdog_timeo; } ;
struct fm10k_ring {int dummy; } ;
struct fm10k_intfc {int num_tx_queues; struct fm10k_ring** tx_ring; } ;

/* Variables and functions */
 int HZ ; 
 int TX_TIMEO_LIMIT ; 
 scalar_t__ check_for_tx_hang (struct fm10k_ring*) ; 
 int /*<<< orphan*/  drv ; 
 scalar_t__ fm10k_check_tx_hang (struct fm10k_ring*) ; 
 int /*<<< orphan*/  fm10k_tx_timeout_reset (struct fm10k_intfc*) ; 
 struct fm10k_intfc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct fm10k_intfc*,int /*<<< orphan*/ ,struct net_device*,char*,int) ; 

__attribute__((used)) static void fm10k_tx_timeout(struct net_device *netdev)
{
	struct fm10k_intfc *interface = netdev_priv(netdev);
	bool real_tx_hang = false;
	int i;

#define TX_TIMEO_LIMIT 16000
	for (i = 0; i < interface->num_tx_queues; i++) {
		struct fm10k_ring *tx_ring = interface->tx_ring[i];

		if (check_for_tx_hang(tx_ring) && fm10k_check_tx_hang(tx_ring))
			real_tx_hang = true;
	}

	if (real_tx_hang) {
		fm10k_tx_timeout_reset(interface);
	} else {
		netif_info(interface, drv, netdev,
			   "Fake Tx hang detected with timeout of %d seconds\n",
			   netdev->watchdog_timeo / HZ);

		/* fake Tx hang - increase the kernel timeout */
		if (netdev->watchdog_timeo < TX_TIMEO_LIMIT)
			netdev->watchdog_timeo *= 2;
	}
}