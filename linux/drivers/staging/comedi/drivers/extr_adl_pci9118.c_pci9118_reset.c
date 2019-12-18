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
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ PCI9118_AI_AUTOSCAN_MODE_REG ; 
 scalar_t__ PCI9118_AI_BURST_NUM_REG ; 
 scalar_t__ PCI9118_AI_CFG_REG ; 
 scalar_t__ PCI9118_AI_CTRL_REG ; 
 scalar_t__ PCI9118_AI_STATUS_REG ; 
 scalar_t__ PCI9118_AO_REG (int) ; 
 scalar_t__ PCI9118_INT_CTRL_REG ; 
 int /*<<< orphan*/  inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int /*<<< orphan*/  pci9118_ai_reset_fifo (struct comedi_device*) ; 

__attribute__((used)) static void pci9118_reset(struct comedi_device *dev)
{
	/* reset analog input subsystem */
	outl(0, dev->iobase + PCI9118_INT_CTRL_REG);
	outl(0, dev->iobase + PCI9118_AI_CTRL_REG);
	outl(0, dev->iobase + PCI9118_AI_CFG_REG);
	pci9118_ai_reset_fifo(dev);

	/* clear any pending interrupts and status */
	inl(dev->iobase + PCI9118_INT_CTRL_REG);
	inl(dev->iobase + PCI9118_AI_STATUS_REG);

	/* reset DMA and scan queue */
	outl(0, dev->iobase + PCI9118_AI_BURST_NUM_REG);
	outl(1, dev->iobase + PCI9118_AI_AUTOSCAN_MODE_REG);
	outl(2, dev->iobase + PCI9118_AI_AUTOSCAN_MODE_REG);

	/* reset analog outputs to 0V */
	outl(2047, dev->iobase + PCI9118_AO_REG(0));
	outl(2047, dev->iobase + PCI9118_AO_REG(1));
}