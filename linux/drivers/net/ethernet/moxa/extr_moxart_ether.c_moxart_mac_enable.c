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
struct moxart_mac_priv_t {int reg_imr; int reg_maccr; scalar_t__ base; } ;

/* Variables and functions */
 int RCV_EN ; 
 int RDMA_EN ; 
 scalar_t__ REG_APOLL_TIMER_CTRL ; 
 scalar_t__ REG_DMA_BLEN_CTRL ; 
 scalar_t__ REG_INTERRUPT_MASK ; 
 scalar_t__ REG_INT_TIMER_CTRL ; 
 scalar_t__ REG_MAC_CTRL ; 
 int RPKT_FINISH_M ; 
 int XDMA_EN ; 
 int XMT_EN ; 
 int XPKT_FINISH_M ; 
 struct moxart_mac_priv_t* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void moxart_mac_enable(struct net_device *ndev)
{
	struct moxart_mac_priv_t *priv = netdev_priv(ndev);

	writel(0x00001010, priv->base + REG_INT_TIMER_CTRL);
	writel(0x00000001, priv->base + REG_APOLL_TIMER_CTRL);
	writel(0x00000390, priv->base + REG_DMA_BLEN_CTRL);

	priv->reg_imr |= (RPKT_FINISH_M | XPKT_FINISH_M);
	writel(priv->reg_imr, priv->base + REG_INTERRUPT_MASK);

	priv->reg_maccr |= (RCV_EN | XMT_EN | RDMA_EN | XDMA_EN);
	writel(priv->reg_maccr, priv->base + REG_MAC_CTRL);
}