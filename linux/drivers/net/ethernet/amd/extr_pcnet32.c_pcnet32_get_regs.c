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
typedef  scalar_t__ ulong ;
typedef  int /*<<< orphan*/  u16 ;
struct pcnet32_private {int phymask; int /*<<< orphan*/  lock; struct pcnet32_access* a; scalar_t__ mii; } ;
struct pcnet32_access {int (* read_csr ) (scalar_t__,int) ;scalar_t__ (* read_bcr ) (scalar_t__,int) ;int /*<<< orphan*/  (* write_bcr ) (scalar_t__,int,int) ;} ;
struct net_device {scalar_t__ base_addr; } ;
struct ethtool_regs {int dummy; } ;

/* Variables and functions */
 int CSR0 ; 
 int CSR0_STOP ; 
 int PCNET32_MAX_PHYS ; 
 int PCNET32_REGS_PER_PHY ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 
 struct pcnet32_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pcnet32_clr_suspend (struct pcnet32_private*,scalar_t__) ; 
 int /*<<< orphan*/  pcnet32_suspend (struct net_device*,unsigned long*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (scalar_t__,int) ; 
 int stub2 (scalar_t__,int) ; 
 int stub3 (scalar_t__,int) ; 
 int stub4 (scalar_t__,int) ; 
 scalar_t__ stub5 (scalar_t__,int) ; 
 scalar_t__ stub6 (scalar_t__,int) ; 
 int /*<<< orphan*/  stub7 (scalar_t__,int,int) ; 
 scalar_t__ stub8 (scalar_t__,int) ; 

__attribute__((used)) static void pcnet32_get_regs(struct net_device *dev, struct ethtool_regs *regs,
			     void *ptr)
{
	int i, csr0;
	u16 *buff = ptr;
	struct pcnet32_private *lp = netdev_priv(dev);
	const struct pcnet32_access *a = lp->a;
	ulong ioaddr = dev->base_addr;
	unsigned long flags;

	spin_lock_irqsave(&lp->lock, flags);

	csr0 = a->read_csr(ioaddr, CSR0);
	if (!(csr0 & CSR0_STOP))	/* If not stopped */
		pcnet32_suspend(dev, &flags, 1);

	/* read address PROM */
	for (i = 0; i < 16; i += 2)
		*buff++ = inw(ioaddr + i);

	/* read control and status registers */
	for (i = 0; i < 90; i++)
		*buff++ = a->read_csr(ioaddr, i);

	*buff++ = a->read_csr(ioaddr, 112);
	*buff++ = a->read_csr(ioaddr, 114);

	/* read bus configuration registers */
	for (i = 0; i < 30; i++)
		*buff++ = a->read_bcr(ioaddr, i);

	*buff++ = 0;		/* skip bcr30 so as not to hang 79C976 */

	for (i = 31; i < 36; i++)
		*buff++ = a->read_bcr(ioaddr, i);

	/* read mii phy registers */
	if (lp->mii) {
		int j;
		for (j = 0; j < PCNET32_MAX_PHYS; j++) {
			if (lp->phymask & (1 << j)) {
				for (i = 0; i < PCNET32_REGS_PER_PHY; i++) {
					lp->a->write_bcr(ioaddr, 33,
							(j << 5) | i);
					*buff++ = lp->a->read_bcr(ioaddr, 34);
				}
			}
		}
	}

	if (!(csr0 & CSR0_STOP))	/* If not stopped */
		pcnet32_clr_suspend(lp, ioaddr);

	spin_unlock_irqrestore(&lp->lock, flags);
}