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
struct altera_tse_private {unsigned int rx_ring_size; unsigned int tx_ring_size; int /*<<< orphan*/ * tx_ring; int /*<<< orphan*/ * rx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct altera_tse_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  tse_free_rx_buffer (struct altera_tse_private*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tse_free_tx_buffer (struct altera_tse_private*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_skbufs(struct net_device *dev)
{
	struct altera_tse_private *priv = netdev_priv(dev);
	unsigned int rx_descs = priv->rx_ring_size;
	unsigned int tx_descs = priv->tx_ring_size;
	int i;

	/* Release the DMA TX/RX socket buffers */
	for (i = 0; i < rx_descs; i++)
		tse_free_rx_buffer(priv, &priv->rx_ring[i]);
	for (i = 0; i < tx_descs; i++)
		tse_free_tx_buffer(priv, &priv->tx_ring[i]);


	kfree(priv->tx_ring);
}