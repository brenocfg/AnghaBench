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

/* Variables and functions */
 int MIIMU_PHYADDR (int) ; 
 int MIIMU_PHY_NRES ; 
 int MIIMU_PREAMBLE ; 
 int MIIMU_REGADDR (int) ; 
 int MIIMU_SNRDY ; 
 int /*<<< orphan*/  NETX_MIIMU ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
netx_eth_phy_read(struct net_device *ndev, int phy_id, int reg)
{
	unsigned int val;

	val = MIIMU_SNRDY | MIIMU_PREAMBLE | MIIMU_PHYADDR(phy_id) |
	      MIIMU_REGADDR(reg) | MIIMU_PHY_NRES;

	writel(val, NETX_MIIMU);
	while (readl(NETX_MIIMU) & MIIMU_SNRDY);

	return readl(NETX_MIIMU) >> 16;

}