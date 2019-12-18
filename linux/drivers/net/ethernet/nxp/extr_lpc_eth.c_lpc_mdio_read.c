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
struct netdata_local {int /*<<< orphan*/  net_base; } ;
struct mii_bus {struct netdata_local* priv; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  LPC_ENET_MADR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_ENET_MCMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_ENET_MIND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_ENET_MRDD (int /*<<< orphan*/ ) ; 
 int LPC_MCMD_READ ; 
 int LPC_MIND_BUSY ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpc_mdio_read(struct mii_bus *bus, int phy_id, int phyreg)
{
	struct netdata_local *pldat = bus->priv;
	unsigned long timeout = jiffies + msecs_to_jiffies(100);
	int lps;

	writel(((phy_id << 8) | phyreg), LPC_ENET_MADR(pldat->net_base));
	writel(LPC_MCMD_READ, LPC_ENET_MCMD(pldat->net_base));

	/* Wait for unbusy status */
	while (readl(LPC_ENET_MIND(pldat->net_base)) & LPC_MIND_BUSY) {
		if (time_after(jiffies, timeout))
			return -EIO;
		cpu_relax();
	}

	lps = readl(LPC_ENET_MRDD(pldat->net_base));
	writel(0, LPC_ENET_MCMD(pldat->net_base));

	return lps;
}