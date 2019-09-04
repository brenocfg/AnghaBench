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
struct sky2_port {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_max_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_MAX_PENDING ; 
 int /*<<< orphan*/  TX_MAX_PENDING ; 
 struct sky2_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void sky2_get_ringparam(struct net_device *dev,
			       struct ethtool_ringparam *ering)
{
	struct sky2_port *sky2 = netdev_priv(dev);

	ering->rx_max_pending = RX_MAX_PENDING;
	ering->tx_max_pending = TX_MAX_PENDING;

	ering->rx_pending = sky2->rx_pending;
	ering->tx_pending = sky2->tx_pending;
}