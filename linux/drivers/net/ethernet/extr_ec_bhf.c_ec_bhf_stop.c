#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  alloc_phys; int /*<<< orphan*/  alloc; int /*<<< orphan*/  alloc_len; } ;
struct TYPE_4__ {int /*<<< orphan*/  alloc_phys; int /*<<< orphan*/  alloc; int /*<<< orphan*/  alloc_len; } ;
struct ec_bhf_priv {TYPE_1__ rx_buf; TYPE_2__ tx_buf; int /*<<< orphan*/  hrtimer; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* PRIV_TO_DEV (struct ec_bhf_priv*) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ec_bhf_reset (struct ec_bhf_priv*) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 struct ec_bhf_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 

__attribute__((used)) static int ec_bhf_stop(struct net_device *net_dev)
{
	struct ec_bhf_priv *priv = netdev_priv(net_dev);
	struct device *dev = PRIV_TO_DEV(priv);

	hrtimer_cancel(&priv->hrtimer);

	ec_bhf_reset(priv);

	netif_tx_disable(net_dev);

	dma_free_coherent(dev, priv->tx_buf.alloc_len,
			  priv->tx_buf.alloc, priv->tx_buf.alloc_phys);
	dma_free_coherent(dev, priv->rx_buf.alloc_len,
			  priv->rx_buf.alloc, priv->rx_buf.alloc_phys);

	return 0;
}