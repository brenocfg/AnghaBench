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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ndesc; } ;
struct ave_private {scalar_t__ base; TYPE_1__ rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVE_DESC_RX_PERMIT ; 
 int /*<<< orphan*/  AVE_DESC_RX_SUSPEND ; 
 scalar_t__ AVE_GISR ; 
 int AVE_GI_RXOVF ; 
 scalar_t__ AVE_GRR ; 
 int AVE_GRR_RXFFR ; 
 scalar_t__ AVE_RXCR ; 
 int AVE_RXCR_RXEN ; 
 int /*<<< orphan*/  ave_desc_switch (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ave_rx_receive (struct net_device*,int /*<<< orphan*/ ) ; 
 struct ave_private* netdev_priv (struct net_device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void ave_rxfifo_reset(struct net_device *ndev)
{
	struct ave_private *priv = netdev_priv(ndev);
	u32 rxcr_org;

	/* save and disable MAC receive op */
	rxcr_org = readl(priv->base + AVE_RXCR);
	writel(rxcr_org & (~AVE_RXCR_RXEN), priv->base + AVE_RXCR);

	/* suspend Rx descriptor */
	ave_desc_switch(ndev, AVE_DESC_RX_SUSPEND);

	/* receive all packets before descriptor starts */
	ave_rx_receive(ndev, priv->rx.ndesc);

	/* assert reset */
	writel(AVE_GRR_RXFFR, priv->base + AVE_GRR);
	udelay(50);

	/* negate reset */
	writel(0, priv->base + AVE_GRR);
	udelay(20);

	/* negate interrupt status */
	writel(AVE_GI_RXOVF, priv->base + AVE_GISR);

	/* permit descriptor */
	ave_desc_switch(ndev, AVE_DESC_RX_PERMIT);

	/* restore MAC reccieve op */
	writel(rxcr_org, priv->base + AVE_RXCR);
}