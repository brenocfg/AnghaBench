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
struct pci9118_private {int ai_cfg; } ;
struct comedi_subdevice {int maxdata; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; struct pci9118_private* private; } ;

/* Variables and functions */
 int PCI9118_AI_CFG_PDTRG ; 
 int PCI9118_AI_CFG_PETRG ; 
 scalar_t__ PCI9118_AI_CFG_REG ; 
 scalar_t__ PCI9118_AI_FIFO_REG ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int /*<<< orphan*/  pci9118_ai_eoc ; 
 int /*<<< orphan*/  pci9118_ai_reset_fifo (struct comedi_device*) ; 
 int /*<<< orphan*/  pci9118_ai_start_conv (struct comedi_device*) ; 
 int /*<<< orphan*/  pci9118_set_chanlist (struct comedi_device*,struct comedi_subdevice*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci9118_ai_insn_read(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn,
				unsigned int *data)
{
	struct pci9118_private *devpriv = dev->private;
	unsigned int val;
	int ret;
	int i;

       /*
	* Configure analog input based on the chanspec.
	* Acqusition is software controlled without interrupts.
	*/
	pci9118_set_chanlist(dev, s, 1, &insn->chanspec, 0, 0);

	/* set default config (disable burst and triggers) */
	devpriv->ai_cfg = PCI9118_AI_CFG_PDTRG | PCI9118_AI_CFG_PETRG;
	outl(devpriv->ai_cfg, dev->iobase + PCI9118_AI_CFG_REG);

	pci9118_ai_reset_fifo(dev);

	for (i = 0; i < insn->n; i++) {
		pci9118_ai_start_conv(dev);

		ret = comedi_timeout(dev, s, insn, pci9118_ai_eoc, 0);
		if (ret)
			return ret;

		val = inl(dev->iobase + PCI9118_AI_FIFO_REG);
		if (s->maxdata == 0xffff)
			data[i] = (val & 0xffff) ^ 0x8000;
		else
			data[i] = (val >> 4) & 0xfff;
	}

	return insn->n;
}