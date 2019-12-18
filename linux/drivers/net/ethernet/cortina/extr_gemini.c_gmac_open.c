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
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  phydev; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/ * function; } ;
struct gemini_ethernet_port {TYPE_1__ rx_coalesce_timer; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int EBUSY ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int geth_resize_freeq (struct gemini_ethernet_port*) ; 
 int /*<<< orphan*/  gmac_cleanup_rxq (struct net_device*) ; 
 int /*<<< orphan*/  gmac_coalesce_delay_expired ; 
 int /*<<< orphan*/  gmac_enable_irq (struct net_device*,int) ; 
 int /*<<< orphan*/  gmac_enable_tx_rx (struct net_device*) ; 
 int /*<<< orphan*/  gmac_irq ; 
 int gmac_setup_phy (struct net_device*) ; 
 int gmac_setup_rxq (struct net_device*) ; 
 int gmac_setup_txqs (struct net_device*) ; 
 int /*<<< orphan*/  gmac_start_dma (struct gemini_ethernet_port*) ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct gemini_ethernet_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct gemini_ethernet_port*,int /*<<< orphan*/ ,struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int gmac_open(struct net_device *netdev)
{
	struct gemini_ethernet_port *port = netdev_priv(netdev);
	int err;

	if (!netdev->phydev) {
		err = gmac_setup_phy(netdev);
		if (err) {
			netif_err(port, ifup, netdev,
				  "PHY init failed: %d\n", err);
			return err;
		}
	}

	err = request_irq(netdev->irq, gmac_irq,
			  IRQF_SHARED, netdev->name, netdev);
	if (err) {
		netdev_err(netdev, "no IRQ\n");
		return err;
	}

	netif_carrier_off(netdev);
	phy_start(netdev->phydev);

	err = geth_resize_freeq(port);
	/* It's fine if it's just busy, the other port has set up
	 * the freeq in that case.
	 */
	if (err && (err != -EBUSY)) {
		netdev_err(netdev, "could not resize freeq\n");
		goto err_stop_phy;
	}

	err = gmac_setup_rxq(netdev);
	if (err) {
		netdev_err(netdev, "could not setup RXQ\n");
		goto err_stop_phy;
	}

	err = gmac_setup_txqs(netdev);
	if (err) {
		netdev_err(netdev, "could not setup TXQs\n");
		gmac_cleanup_rxq(netdev);
		goto err_stop_phy;
	}

	napi_enable(&port->napi);

	gmac_start_dma(port);
	gmac_enable_irq(netdev, 1);
	gmac_enable_tx_rx(netdev);
	netif_tx_start_all_queues(netdev);

	hrtimer_init(&port->rx_coalesce_timer, CLOCK_MONOTONIC,
		     HRTIMER_MODE_REL);
	port->rx_coalesce_timer.function = &gmac_coalesce_delay_expired;

	netdev_dbg(netdev, "opened\n");

	return 0;

err_stop_phy:
	phy_stop(netdev->phydev);
	free_irq(netdev->irq, netdev);
	return err;
}