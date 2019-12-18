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
struct ioc3_private {int rx_ci; int rx_pi; int tx_pi; int tx_ci; int emcr; scalar_t__ txqlen; int /*<<< orphan*/  txr_dma; int /*<<< orphan*/  rxr_dma; struct ioc3_ethregs* regs; } ;
struct ioc3_ethregs {int /*<<< orphan*/  eier; int /*<<< orphan*/  emcr; int /*<<< orphan*/  etcir; int /*<<< orphan*/  etpir; int /*<<< orphan*/  etbr_l; int /*<<< orphan*/  etbr_h; int /*<<< orphan*/  erpir; int /*<<< orphan*/  ercir; int /*<<< orphan*/  erbr_l; int /*<<< orphan*/  erbr_h; } ;

/* Variables and functions */
 int EISR_RXBUFOFLO ; 
 int EISR_RXMEMERR ; 
 int EISR_RXOFLO ; 
 int EISR_RXPARERR ; 
 int EISR_RXTIMERINT ; 
 int EISR_TXBUFUFLO ; 
 int EISR_TXEXPLICIT ; 
 int EISR_TXMEMERR ; 
 int EMCR_PADEN ; 
 int EMCR_RXDMAEN ; 
 int EMCR_RXEN ; 
 int EMCR_RXOFF_SHIFT ; 
 int EMCR_TXDMAEN ; 
 int EMCR_TXEN ; 
 int ERPIR_ARM ; 
 int /*<<< orphan*/  PCI64_ATTR_PREC ; 
 int RX_OFFSET ; 
 unsigned long ioc3_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ioc3_start(struct ioc3_private *ip)
{
	struct ioc3_ethregs *regs = ip->regs;
	unsigned long ring;

	/* Now the rx ring base, consume & produce registers.  */
	ring = ioc3_map(ip->rxr_dma, PCI64_ATTR_PREC);
	writel(ring >> 32, &regs->erbr_h);
	writel(ring & 0xffffffff, &regs->erbr_l);
	writel(ip->rx_ci << 3, &regs->ercir);
	writel((ip->rx_pi << 3) | ERPIR_ARM, &regs->erpir);

	ring = ioc3_map(ip->txr_dma, PCI64_ATTR_PREC);

	ip->txqlen = 0;					/* nothing queued  */

	/* Now the tx ring base, consume & produce registers.  */
	writel(ring >> 32, &regs->etbr_h);
	writel(ring & 0xffffffff, &regs->etbr_l);
	writel(ip->tx_pi << 7, &regs->etpir);
	writel(ip->tx_ci << 7, &regs->etcir);
	readl(&regs->etcir);				/* Flush */

	ip->emcr |= ((RX_OFFSET / 2) << EMCR_RXOFF_SHIFT) | EMCR_TXDMAEN |
		    EMCR_TXEN | EMCR_RXDMAEN | EMCR_RXEN | EMCR_PADEN;
	writel(ip->emcr, &regs->emcr);
	writel(EISR_RXTIMERINT | EISR_RXOFLO | EISR_RXBUFOFLO |
	       EISR_RXMEMERR | EISR_RXPARERR | EISR_TXBUFUFLO |
	       EISR_TXEXPLICIT | EISR_TXMEMERR, &regs->eier);
	readl(&regs->eier);
}