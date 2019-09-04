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
struct au1000_private {TYPE_1__* mac; } ;
struct TYPE_2__ {int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int MAC_RX_ENABLE ; 
 int MAC_TX_ENABLE ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct au1000_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct au1000_private*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void au1000_enable_rx_tx(struct net_device *dev)
{
	struct au1000_private *aup = netdev_priv(dev);
	u32 reg;

	netif_dbg(aup, hw, dev, "enable_rx_tx\n");

	reg = readl(&aup->mac->control);
	reg |= (MAC_RX_ENABLE | MAC_TX_ENABLE);
	writel(reg, &aup->mac->control);
	wmb(); /* drain writebuffer */
	mdelay(10);
}