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
struct comedi_subdevice {unsigned int* readback; scalar_t__ private; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned long PCI1724_DAC_CTRL_CX (unsigned int) ; 
 unsigned int PCI1724_DAC_CTRL_DATA (unsigned int) ; 
 unsigned long PCI1724_DAC_CTRL_GX (unsigned int) ; 
 scalar_t__ PCI1724_DAC_CTRL_REG ; 
 scalar_t__ PCI1724_SYNC_CTRL_REG ; 
 int /*<<< orphan*/  adv_pci1724_dac_idle ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 

__attribute__((used)) static int adv_pci1724_insn_write(struct comedi_device *dev,
				  struct comedi_subdevice *s,
				  struct comedi_insn *insn,
				  unsigned int *data)
{
	unsigned long mode = (unsigned long)s->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int ctrl;
	int ret;
	int i;

	ctrl = PCI1724_DAC_CTRL_GX(chan) | PCI1724_DAC_CTRL_CX(chan) | mode;

	/* turn off synchronous mode */
	outl(0, dev->iobase + PCI1724_SYNC_CTRL_REG);

	for (i = 0; i < insn->n; ++i) {
		unsigned int val = data[i];

		ret = comedi_timeout(dev, s, insn, adv_pci1724_dac_idle, 0);
		if (ret)
			return ret;

		outl(ctrl | PCI1724_DAC_CTRL_DATA(val),
		     dev->iobase + PCI1724_DAC_CTRL_REG);

		s->readback[chan] = val;
	}

	return insn->n;
}