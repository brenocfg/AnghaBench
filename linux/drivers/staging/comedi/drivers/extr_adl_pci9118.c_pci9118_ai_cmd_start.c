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
struct pci9118_private {int ai_do; int /*<<< orphan*/  ai_ctrl; int /*<<< orphan*/  ai_cfg; int /*<<< orphan*/  int_ctrl; } ;
struct comedi_device {scalar_t__ iobase; struct pci9118_private* private; } ;

/* Variables and functions */
 scalar_t__ PCI9118_AI_CFG_REG ; 
 scalar_t__ PCI9118_AI_CTRL_REG ; 
 int /*<<< orphan*/  PCI9118_AI_CTRL_SOFTG ; 
 scalar_t__ PCI9118_INT_CTRL_REG ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci9118_start_pacer (struct comedi_device*,int) ; 

__attribute__((used)) static void pci9118_ai_cmd_start(struct comedi_device *dev)
{
	struct pci9118_private *devpriv = dev->private;

	outl(devpriv->int_ctrl, dev->iobase + PCI9118_INT_CTRL_REG);
	outl(devpriv->ai_cfg, dev->iobase + PCI9118_AI_CFG_REG);
	if (devpriv->ai_do != 3) {
		pci9118_start_pacer(dev, devpriv->ai_do);
		devpriv->ai_ctrl |= PCI9118_AI_CTRL_SOFTG;
	}
	outl(devpriv->ai_ctrl, dev->iobase + PCI9118_AI_CTRL_REG);
}