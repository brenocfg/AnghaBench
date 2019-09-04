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
struct mbox_chan {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct mbox_chan* chans; struct device* dev; } ;
struct bcm2835_mbox {scalar_t__ regs; TYPE_1__ controller; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int ARM_MS_EMPTY ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ MAIL0_RD ; 
 scalar_t__ MAIL0_STA ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  mbox_chan_received_data (struct mbox_chan*,int*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static irqreturn_t bcm2835_mbox_irq(int irq, void *dev_id)
{
	struct bcm2835_mbox *mbox = dev_id;
	struct device *dev = mbox->controller.dev;
	struct mbox_chan *link = &mbox->controller.chans[0];

	while (!(readl(mbox->regs + MAIL0_STA) & ARM_MS_EMPTY)) {
		u32 msg = readl(mbox->regs + MAIL0_RD);
		dev_dbg(dev, "Reply 0x%08X\n", msg);
		mbox_chan_received_data(link, &msg);
	}
	return IRQ_HANDLED;
}