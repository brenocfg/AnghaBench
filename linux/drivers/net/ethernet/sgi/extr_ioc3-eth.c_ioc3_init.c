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
struct ioc3_private {int ehar_h; int ehar_l; int /*<<< orphan*/  ioc3_timer; struct ioc3_ethregs* regs; } ;
struct ioc3_ethregs {int /*<<< orphan*/  ersr; int /*<<< orphan*/  ehar_l; int /*<<< orphan*/  ehar_h; int /*<<< orphan*/  ertr; int /*<<< orphan*/  ercsr; int /*<<< orphan*/  etcdc; int /*<<< orphan*/  erbar; int /*<<< orphan*/  emcr; } ;

/* Variables and functions */
 int EMCR_RST ; 
 int ERBAR_VAL ; 
 int /*<<< orphan*/  __ioc3_set_mac_address (struct net_device*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct ioc3_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ioc3_init(struct net_device *dev)
{
	struct ioc3_private *ip = netdev_priv(dev);
	struct ioc3_ethregs *regs = ip->regs;

	del_timer_sync(&ip->ioc3_timer);	/* Kill if running	*/

	writel(EMCR_RST, &regs->emcr);		/* Reset		*/
	readl(&regs->emcr);			/* Flush WB		*/
	udelay(4);				/* Give it time ...	*/
	writel(0, &regs->emcr);
	readl(&regs->emcr);

	/* Misc registers  */
	writel(ERBAR_VAL, &regs->erbar);
	readl(&regs->etcdc);			/* Clear on read */
	writel(15, &regs->ercsr);		/* RX low watermark  */
	writel(0, &regs->ertr);			/* Interrupt immediately */
	__ioc3_set_mac_address(dev);
	writel(ip->ehar_h, &regs->ehar_h);
	writel(ip->ehar_l, &regs->ehar_l);
	writel(42, &regs->ersr);		/* XXX should be random */
}