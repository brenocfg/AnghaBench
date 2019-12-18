#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  rx_dropped; } ;
struct net_device {TYPE_1__ stats; } ;
struct ftmac100_rxdes {int dummy; } ;
struct ftmac100 {struct net_device* netdev; } ;

/* Variables and functions */
 struct ftmac100_rxdes* ftmac100_current_rxdes (struct ftmac100*) ; 
 int /*<<< orphan*/  ftmac100_rx_pointer_advance (struct ftmac100*) ; 
 scalar_t__ ftmac100_rxdes_last_segment (struct ftmac100_rxdes*) ; 
 int /*<<< orphan*/  ftmac100_rxdes_owned_by_dma (struct ftmac100_rxdes*) ; 
 int /*<<< orphan*/  ftmac100_rxdes_set_dma_own (struct ftmac100_rxdes*) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,struct ftmac100_rxdes*) ; 

__attribute__((used)) static void ftmac100_rx_drop_packet(struct ftmac100 *priv)
{
	struct net_device *netdev = priv->netdev;
	struct ftmac100_rxdes *rxdes = ftmac100_current_rxdes(priv);
	bool done = false;

	if (net_ratelimit())
		netdev_dbg(netdev, "drop packet %p\n", rxdes);

	do {
		if (ftmac100_rxdes_last_segment(rxdes))
			done = true;

		ftmac100_rxdes_set_dma_own(rxdes);
		ftmac100_rx_pointer_advance(priv);
		rxdes = ftmac100_current_rxdes(priv);
	} while (!done && !ftmac100_rxdes_owned_by_dma(rxdes));

	netdev->stats.rx_dropped++;
}