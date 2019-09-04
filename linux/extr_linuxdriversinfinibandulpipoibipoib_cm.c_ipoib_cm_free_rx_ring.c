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
struct ipoib_dev_priv {int dummy; } ;
struct ipoib_cm_rx_buf {scalar_t__ skb; int /*<<< orphan*/  mapping; } ;

/* Variables and functions */
 scalar_t__ IPOIB_CM_RX_SG ; 
 int /*<<< orphan*/  dev_kfree_skb_any (scalar_t__) ; 
 int /*<<< orphan*/  ipoib_cm_dma_unmap_rx (struct ipoib_dev_priv*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int ipoib_recvq_size ; 
 int /*<<< orphan*/  vfree (struct ipoib_cm_rx_buf*) ; 

__attribute__((used)) static void ipoib_cm_free_rx_ring(struct net_device *dev,
				  struct ipoib_cm_rx_buf *rx_ring)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);
	int i;

	for (i = 0; i < ipoib_recvq_size; ++i)
		if (rx_ring[i].skb) {
			ipoib_cm_dma_unmap_rx(priv, IPOIB_CM_RX_SG - 1,
					      rx_ring[i].mapping);
			dev_kfree_skb_any(rx_ring[i].skb);
		}

	vfree(rx_ring);
}