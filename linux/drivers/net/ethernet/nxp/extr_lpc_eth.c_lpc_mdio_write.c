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
typedef  int u16 ;
struct netdata_local {int /*<<< orphan*/  net_base; } ;
struct mii_bus {struct netdata_local* priv; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  LPC_ENET_MADR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_ENET_MIND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_ENET_MWTD (int /*<<< orphan*/ ) ; 
 int LPC_MIND_BUSY ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpc_mdio_write(struct mii_bus *bus, int phy_id, int phyreg,
			u16 phydata)
{
	struct netdata_local *pldat = bus->priv;
	unsigned long timeout = jiffies + msecs_to_jiffies(100);

	writel(((phy_id << 8) | phyreg), LPC_ENET_MADR(pldat->net_base));
	writel(phydata, LPC_ENET_MWTD(pldat->net_base));

	/* Wait for completion */
	while (readl(LPC_ENET_MIND(pldat->net_base)) & LPC_MIND_BUSY) {
		if (time_after(jiffies, timeout))
			return -EIO;
		cpu_relax();
	}

	return 0;
}