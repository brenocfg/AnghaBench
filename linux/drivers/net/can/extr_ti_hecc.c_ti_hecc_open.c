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
struct ti_hecc_priv {int /*<<< orphan*/  offload; } ;
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_LED_EVENT_OPEN ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_rx_offload_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 struct ti_hecc_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int open_candev (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  ti_hecc_interrupt ; 
 int /*<<< orphan*/  ti_hecc_start (struct net_device*) ; 
 int /*<<< orphan*/  ti_hecc_transceiver_switch (struct ti_hecc_priv*,int) ; 

__attribute__((used)) static int ti_hecc_open(struct net_device *ndev)
{
	struct ti_hecc_priv *priv = netdev_priv(ndev);
	int err;

	err = request_irq(ndev->irq, ti_hecc_interrupt, IRQF_SHARED,
			  ndev->name, ndev);
	if (err) {
		netdev_err(ndev, "error requesting interrupt\n");
		return err;
	}

	ti_hecc_transceiver_switch(priv, 1);

	/* Open common can device */
	err = open_candev(ndev);
	if (err) {
		netdev_err(ndev, "open_candev() failed %d\n", err);
		ti_hecc_transceiver_switch(priv, 0);
		free_irq(ndev->irq, ndev);
		return err;
	}

	can_led_event(ndev, CAN_LED_EVENT_OPEN);

	ti_hecc_start(ndev);
	can_rx_offload_enable(&priv->offload);
	netif_start_queue(ndev);

	return 0;
}