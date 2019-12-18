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
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; } ;
struct device {int dummy; } ;
struct net_device {TYPE_1__ stats; struct device dev; } ;
struct emac_priv {int /*<<< orphan*/  txchan; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpdma_chan_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpdma_chan_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  emac_int_disable (struct emac_priv*) ; 
 int /*<<< orphan*/  emac_int_enable (struct emac_priv*) ; 
 struct emac_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_tx_err (struct emac_priv*) ; 

__attribute__((used)) static void emac_dev_tx_timeout(struct net_device *ndev)
{
	struct emac_priv *priv = netdev_priv(ndev);
	struct device *emac_dev = &ndev->dev;

	if (netif_msg_tx_err(priv))
		dev_err(emac_dev, "DaVinci EMAC: xmit timeout, restarting TX");

	ndev->stats.tx_errors++;
	emac_int_disable(priv);
	cpdma_chan_stop(priv->txchan);
	cpdma_chan_start(priv->txchan);
	emac_int_enable(priv);
}