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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct gem {int mac_rx_cfg; scalar_t__ regs; int /*<<< orphan*/  cell_enabled; scalar_t__ reset_task_pending; } ;

/* Variables and functions */
 scalar_t__ MAC_RXCFG ; 
 int MAC_RXCFG_ENAB ; 
 int MAC_RXCFG_HFE ; 
 int MAC_RXCFG_PROM ; 
 int MAC_RXCFG_SFCS ; 
 scalar_t__ WARN_ON (int) ; 
 int gem_setup_multicast (struct gem*) ; 
 struct gem* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_present (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void gem_set_multicast(struct net_device *dev)
{
	struct gem *gp = netdev_priv(dev);
	u32 rxcfg, rxcfg_new;
	int limit = 10000;

	if (!netif_running(dev) || !netif_device_present(dev))
		return;

	/* Better safe than sorry... */
	if (gp->reset_task_pending || WARN_ON(!gp->cell_enabled))
		return;

	rxcfg = readl(gp->regs + MAC_RXCFG);
	rxcfg_new = gem_setup_multicast(gp);
#ifdef STRIP_FCS
	rxcfg_new |= MAC_RXCFG_SFCS;
#endif
	gp->mac_rx_cfg = rxcfg_new;

	writel(rxcfg & ~MAC_RXCFG_ENAB, gp->regs + MAC_RXCFG);
	while (readl(gp->regs + MAC_RXCFG) & MAC_RXCFG_ENAB) {
		if (!limit--)
			break;
		udelay(10);
	}

	rxcfg &= ~(MAC_RXCFG_PROM | MAC_RXCFG_HFE);
	rxcfg |= rxcfg_new;

	writel(rxcfg, gp->regs + MAC_RXCFG);
}