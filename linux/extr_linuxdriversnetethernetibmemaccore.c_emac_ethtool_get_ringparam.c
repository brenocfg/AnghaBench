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
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  rx_max_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  NUM_RX_BUFF ; 
 int /*<<< orphan*/  NUM_TX_BUFF ; 

__attribute__((used)) static void emac_ethtool_get_ringparam(struct net_device *ndev,
				       struct ethtool_ringparam *rp)
{
	rp->rx_max_pending = rp->rx_pending = NUM_RX_BUFF;
	rp->tx_max_pending = rp->tx_pending = NUM_TX_BUFF;
}