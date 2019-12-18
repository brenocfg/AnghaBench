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
struct ioc3_private {struct ioc3_ethregs* regs; } ;
struct ioc3_ethregs {int /*<<< orphan*/  midr_r; int /*<<< orphan*/  micr; } ;

/* Variables and functions */
 int MICR_BUSY ; 
 int MICR_PHYADDR_SHIFT ; 
 int MICR_READTRIG ; 
 int MIDR_DATA_MASK ; 
 struct ioc3_private* netdev_priv (struct net_device*) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ioc3_mdio_read(struct net_device *dev, int phy, int reg)
{
	struct ioc3_private *ip = netdev_priv(dev);
	struct ioc3_ethregs *regs = ip->regs;

	while (readl(&regs->micr) & MICR_BUSY)
		;
	writel((phy << MICR_PHYADDR_SHIFT) | reg | MICR_READTRIG,
	       &regs->micr);
	while (readl(&regs->micr) & MICR_BUSY)
		;

	return readl(&regs->midr_r) & MIDR_DATA_MASK;
}