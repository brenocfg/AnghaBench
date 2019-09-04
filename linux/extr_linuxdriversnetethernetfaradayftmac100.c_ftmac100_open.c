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
struct net_device {int /*<<< orphan*/  name; } ;
struct ftmac100 {int /*<<< orphan*/  irq; int /*<<< orphan*/  napi; scalar_t__ tx_pending; scalar_t__ tx_pointer; scalar_t__ tx_clean_pointer; scalar_t__ rx_pointer; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int ftmac100_alloc_buffers (struct ftmac100*) ; 
 int /*<<< orphan*/  ftmac100_enable_all_int (struct ftmac100*) ; 
 int /*<<< orphan*/  ftmac100_free_buffers (struct ftmac100*) ; 
 int /*<<< orphan*/  ftmac100_interrupt ; 
 int ftmac100_start_hw (struct ftmac100*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 struct ftmac100* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int ftmac100_open(struct net_device *netdev)
{
	struct ftmac100 *priv = netdev_priv(netdev);
	int err;

	err = ftmac100_alloc_buffers(priv);
	if (err) {
		netdev_err(netdev, "failed to allocate buffers\n");
		goto err_alloc;
	}

	err = request_irq(priv->irq, ftmac100_interrupt, 0, netdev->name, netdev);
	if (err) {
		netdev_err(netdev, "failed to request irq %d\n", priv->irq);
		goto err_irq;
	}

	priv->rx_pointer = 0;
	priv->tx_clean_pointer = 0;
	priv->tx_pointer = 0;
	priv->tx_pending = 0;

	err = ftmac100_start_hw(priv);
	if (err)
		goto err_hw;

	napi_enable(&priv->napi);
	netif_start_queue(netdev);

	ftmac100_enable_all_int(priv);

	return 0;

err_hw:
	free_irq(priv->irq, netdev);
err_irq:
	ftmac100_free_buffers(priv);
err_alloc:
	return err;
}