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
struct fritz_adapter {int /*<<< orphan*/  isac; scalar_t__ io; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned char AVM_STATUS0_IRQ_HDLC ; 
 unsigned char AVM_STATUS0_IRQ_ISAC ; 
 unsigned char AVM_STATUS0_IRQ_MASK ; 
 int /*<<< orphan*/  DBG (int,char*,unsigned char) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  hdlc_irq (struct fritz_adapter*) ; 
 unsigned char inb (scalar_t__) ; 
 int /*<<< orphan*/  isac_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t
fcpci_irq(int intno, void *dev)
{
	struct fritz_adapter *adapter = dev;
	unsigned char sval;

	sval = inb(adapter->io + 2);
	if ((sval & AVM_STATUS0_IRQ_MASK) == AVM_STATUS0_IRQ_MASK)
		/* possibly a shared  IRQ reqest */
		return IRQ_NONE;
	DBG(2, "sval %#x", sval);
	if (!(sval & AVM_STATUS0_IRQ_ISAC))
		isac_irq(&adapter->isac);

	if (!(sval & AVM_STATUS0_IRQ_HDLC))
		hdlc_irq(adapter);
	return IRQ_HANDLED;
}