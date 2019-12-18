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
struct tw68_dev {int pci_irqmask; int board_virqmask; int /*<<< orphan*/  name; TYPE_1__* pci; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  TW68_INTMASK ; 
 int /*<<< orphan*/  TW68_INTSTAT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tw68_irq_video_done (struct tw68_dev*,int) ; 
 int /*<<< orphan*/  tw_clearl (int /*<<< orphan*/ ,int) ; 
 int tw_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t tw68_irq(int irq, void *dev_id)
{
	struct tw68_dev *dev = dev_id;
	u32 status, orig;
	int loop;

	status = orig = tw_readl(TW68_INTSTAT) & dev->pci_irqmask;
	/* Check if anything to do */
	if (0 == status)
		return IRQ_NONE;	/* Nope - return */
	for (loop = 0; loop < 10; loop++) {
		if (status & dev->board_virqmask)	/* video interrupt */
			tw68_irq_video_done(dev, status);
		status = tw_readl(TW68_INTSTAT) & dev->pci_irqmask;
		if (0 == status)
			return IRQ_HANDLED;
	}
	dev_dbg(&dev->pci->dev, "%s: **** INTERRUPT NOT HANDLED - clearing mask (orig 0x%08x, cur 0x%08x)",
			dev->name, orig, tw_readl(TW68_INTSTAT));
	dev_dbg(&dev->pci->dev, "%s: pci_irqmask 0x%08x; board_virqmask 0x%08x ****\n",
			dev->name, dev->pci_irqmask, dev->board_virqmask);
	tw_clearl(TW68_INTMASK, dev->pci_irqmask);
	return IRQ_HANDLED;
}