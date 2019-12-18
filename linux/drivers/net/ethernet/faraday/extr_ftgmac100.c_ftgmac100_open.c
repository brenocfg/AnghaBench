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
struct net_device {int /*<<< orphan*/  irq; scalar_t__ phydev; int /*<<< orphan*/  name; } ;
struct ftgmac100 {scalar_t__ base; int /*<<< orphan*/  napi; int /*<<< orphan*/  ndev; scalar_t__ use_ncsi; scalar_t__ cur_speed; scalar_t__ cur_duplex; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ FTGMAC100_OFFSET_IER ; 
 scalar_t__ SPEED_100 ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int ftgmac100_alloc_rings (struct ftgmac100*) ; 
 int /*<<< orphan*/  ftgmac100_free_buffers (struct ftgmac100*) ; 
 int /*<<< orphan*/  ftgmac100_free_rings (struct ftgmac100*) ; 
 int ftgmac100_init_all (struct ftgmac100*,int) ; 
 int /*<<< orphan*/  ftgmac100_interrupt ; 
 int /*<<< orphan*/  ftgmac100_poll ; 
 int ftgmac100_reset_and_config_mac (struct ftgmac100*) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int ncsi_start_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 struct ftgmac100* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_start (scalar_t__) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int ftgmac100_open(struct net_device *netdev)
{
	struct ftgmac100 *priv = netdev_priv(netdev);
	int err;

	/* Allocate ring buffers  */
	err = ftgmac100_alloc_rings(priv);
	if (err) {
		netdev_err(netdev, "Failed to allocate descriptors\n");
		return err;
	}

	/* When using NC-SI we force the speed to 100Mbit/s full duplex,
	 *
	 * Otherwise we leave it set to 0 (no link), the link
	 * message from the PHY layer will handle setting it up to
	 * something else if needed.
	 */
	if (priv->use_ncsi) {
		priv->cur_duplex = DUPLEX_FULL;
		priv->cur_speed = SPEED_100;
	} else {
		priv->cur_duplex = 0;
		priv->cur_speed = 0;
	}

	/* Reset the hardware */
	err = ftgmac100_reset_and_config_mac(priv);
	if (err)
		goto err_hw;

	/* Initialize NAPI */
	netif_napi_add(netdev, &priv->napi, ftgmac100_poll, 64);

	/* Grab our interrupt */
	err = request_irq(netdev->irq, ftgmac100_interrupt, 0, netdev->name, netdev);
	if (err) {
		netdev_err(netdev, "failed to request irq %d\n", netdev->irq);
		goto err_irq;
	}

	/* Start things up */
	err = ftgmac100_init_all(priv, false);
	if (err) {
		netdev_err(netdev, "Failed to allocate packet buffers\n");
		goto err_alloc;
	}

	if (netdev->phydev) {
		/* If we have a PHY, start polling */
		phy_start(netdev->phydev);
	} else if (priv->use_ncsi) {
		/* If using NC-SI, set our carrier on and start the stack */
		netif_carrier_on(netdev);

		/* Start the NCSI device */
		err = ncsi_start_dev(priv->ndev);
		if (err)
			goto err_ncsi;
	}

	return 0;

 err_ncsi:
	napi_disable(&priv->napi);
	netif_stop_queue(netdev);
 err_alloc:
	ftgmac100_free_buffers(priv);
	free_irq(netdev->irq, netdev);
 err_irq:
	netif_napi_del(&priv->napi);
 err_hw:
	iowrite32(0, priv->base + FTGMAC100_OFFSET_IER);
	ftgmac100_free_rings(priv);
	return err;
}