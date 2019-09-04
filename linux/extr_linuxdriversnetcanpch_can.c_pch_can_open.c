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
struct pch_can_priv {TYPE_1__* dev; int /*<<< orphan*/  napi; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 struct pch_can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int open_candev (struct net_device*) ; 
 int /*<<< orphan*/  pch_can_init (struct pch_can_priv*) ; 
 int /*<<< orphan*/  pch_can_interrupt ; 
 int /*<<< orphan*/  pch_can_release (struct pch_can_priv*) ; 
 int /*<<< orphan*/  pch_can_start (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int pch_can_open(struct net_device *ndev)
{
	struct pch_can_priv *priv = netdev_priv(ndev);
	int retval;

	/* Regstering the interrupt. */
	retval = request_irq(priv->dev->irq, pch_can_interrupt, IRQF_SHARED,
			     ndev->name, ndev);
	if (retval) {
		netdev_err(ndev, "request_irq failed.\n");
		goto req_irq_err;
	}

	/* Open common can device */
	retval = open_candev(ndev);
	if (retval) {
		netdev_err(ndev, "open_candev() failed %d\n", retval);
		goto err_open_candev;
	}

	pch_can_init(priv);
	pch_can_start(ndev);
	napi_enable(&priv->napi);
	netif_start_queue(ndev);

	return 0;

err_open_candev:
	free_irq(priv->dev->irq, ndev);
req_irq_err:
	pch_can_release(priv);

	return retval;
}