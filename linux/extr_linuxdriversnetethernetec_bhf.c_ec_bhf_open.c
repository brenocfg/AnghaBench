#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tx_desc {int dummy; } ;
struct rx_desc {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  alloc_len; int /*<<< orphan*/  alloc; } ;
struct TYPE_4__ {int /*<<< orphan*/  function; } ;
struct ec_bhf_priv {TYPE_3__ rx_buf; TYPE_1__ hrtimer; scalar_t__ mii_io; int /*<<< orphan*/  tx_dma_chan; TYPE_3__ tx_buf; int /*<<< orphan*/  rx_dma_chan; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int FIFO_SIZE ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 scalar_t__ MII_MAC_FILT_FLAG ; 
 struct device* PRIV_TO_DEV (struct ec_bhf_priv*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ec_bhf_alloc_dma_mem (struct ec_bhf_priv*,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ec_bhf_reset (struct ec_bhf_priv*) ; 
 int /*<<< orphan*/  ec_bhf_setup_rx_descs (struct ec_bhf_priv*) ; 
 int /*<<< orphan*/  ec_bhf_setup_tx_descs (struct ec_bhf_priv*) ; 
 int /*<<< orphan*/  ec_bhf_timer_fun ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_start (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,scalar_t__) ; 
 struct ec_bhf_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  polling_frequency ; 

__attribute__((used)) static int ec_bhf_open(struct net_device *net_dev)
{
	struct ec_bhf_priv *priv = netdev_priv(net_dev);
	struct device *dev = PRIV_TO_DEV(priv);
	int err = 0;

	ec_bhf_reset(priv);

	err = ec_bhf_alloc_dma_mem(priv, &priv->rx_buf, priv->rx_dma_chan,
				   FIFO_SIZE * sizeof(struct rx_desc));
	if (err) {
		dev_err(dev, "Failed to allocate rx buffer\n");
		goto out;
	}
	ec_bhf_setup_rx_descs(priv);

	err = ec_bhf_alloc_dma_mem(priv, &priv->tx_buf, priv->tx_dma_chan,
				   FIFO_SIZE * sizeof(struct tx_desc));
	if (err) {
		dev_err(dev, "Failed to allocate tx buffer\n");
		goto error_rx_free;
	}
	iowrite8(0, priv->mii_io + MII_MAC_FILT_FLAG);
	ec_bhf_setup_tx_descs(priv);

	netif_start_queue(net_dev);

	hrtimer_init(&priv->hrtimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	priv->hrtimer.function = ec_bhf_timer_fun;
	hrtimer_start(&priv->hrtimer, polling_frequency, HRTIMER_MODE_REL);

	return 0;

error_rx_free:
	dma_free_coherent(dev, priv->rx_buf.alloc_len, priv->rx_buf.alloc,
			  priv->rx_buf.alloc_len);
out:
	return err;
}