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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct mpc52xx_fec_priv {int /*<<< orphan*/  rx_dmatsk; } ;
struct bcom_fec_bd {int /*<<< orphan*/  skb_pa; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  FEC_RX_BUFFER_SIZE ; 
 scalar_t__ bcom_prepare_next_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcom_submit_next_buffer (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mpc52xx_fec_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
mpc52xx_fec_rx_submit(struct net_device *dev, struct sk_buff *rskb)
{
	struct mpc52xx_fec_priv *priv = netdev_priv(dev);
	struct bcom_fec_bd *bd;

	bd = (struct bcom_fec_bd *) bcom_prepare_next_buffer(priv->rx_dmatsk);
	bd->status = FEC_RX_BUFFER_SIZE;
	bd->skb_pa = dma_map_single(dev->dev.parent, rskb->data,
				    FEC_RX_BUFFER_SIZE, DMA_FROM_DEVICE);
	bcom_submit_next_buffer(priv->rx_dmatsk, rskb);
}