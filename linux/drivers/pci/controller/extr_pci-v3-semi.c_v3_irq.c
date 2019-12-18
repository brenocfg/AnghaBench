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
struct v3_pci {scalar_t__ map; scalar_t__ base; struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int INTEGRATOR_SC_PCI_ENABLE ; 
 int INTEGRATOR_SC_PCI_INTCLR ; 
 int /*<<< orphan*/  INTEGRATOR_SC_PCI_OFFSET ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ V3_LB_ISTAT ; 
 int V3_LB_ISTAT_DMA0 ; 
 int V3_LB_ISTAT_DMA1 ; 
 int V3_LB_ISTAT_I2O_QWR ; 
 int V3_LB_ISTAT_MAILBOX ; 
 int V3_LB_ISTAT_PCI_INT ; 
 int V3_LB_ISTAT_PCI_PERR ; 
 int V3_LB_ISTAT_PCI_RD ; 
 int V3_LB_ISTAT_PCI_WR ; 
 scalar_t__ V3_PCI_STAT ; 
 int V3_PCI_STAT_M_ABORT_ERR ; 
 int V3_PCI_STAT_PAR_ERR ; 
 int V3_PCI_STAT_SYS_ERR ; 
 int V3_PCI_STAT_T_ABORT_ERR ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int readb (scalar_t__) ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  regmap_write (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t v3_irq(int irq, void *data)
{
	struct v3_pci *v3 = data;
	struct device *dev = v3->dev;
	u32 status;

	status = readw(v3->base + V3_PCI_STAT);
	if (status & V3_PCI_STAT_PAR_ERR)
		dev_err(dev, "parity error interrupt\n");
	if (status & V3_PCI_STAT_SYS_ERR)
		dev_err(dev, "system error interrupt\n");
	if (status & V3_PCI_STAT_M_ABORT_ERR)
		dev_err(dev, "master abort error interrupt\n");
	if (status & V3_PCI_STAT_T_ABORT_ERR)
		dev_err(dev, "target abort error interrupt\n");
	writew(status, v3->base + V3_PCI_STAT);

	status = readb(v3->base + V3_LB_ISTAT);
	if (status & V3_LB_ISTAT_MAILBOX)
		dev_info(dev, "PCI mailbox interrupt\n");
	if (status & V3_LB_ISTAT_PCI_RD)
		dev_err(dev, "PCI target LB->PCI READ abort interrupt\n");
	if (status & V3_LB_ISTAT_PCI_WR)
		dev_err(dev, "PCI target LB->PCI WRITE abort interrupt\n");
	if (status &  V3_LB_ISTAT_PCI_INT)
		dev_info(dev, "PCI pin interrupt\n");
	if (status & V3_LB_ISTAT_PCI_PERR)
		dev_err(dev, "PCI parity error interrupt\n");
	if (status & V3_LB_ISTAT_I2O_QWR)
		dev_info(dev, "I2O inbound post queue interrupt\n");
	if (status & V3_LB_ISTAT_DMA1)
		dev_info(dev, "DMA channel 1 interrupt\n");
	if (status & V3_LB_ISTAT_DMA0)
		dev_info(dev, "DMA channel 0 interrupt\n");
	/* Clear all possible interrupts on the local bus */
	writeb(0, v3->base + V3_LB_ISTAT);
	if (v3->map)
		regmap_write(v3->map, INTEGRATOR_SC_PCI_OFFSET,
			     INTEGRATOR_SC_PCI_ENABLE |
			     INTEGRATOR_SC_PCI_INTCLR);

	return IRQ_HANDLED;
}