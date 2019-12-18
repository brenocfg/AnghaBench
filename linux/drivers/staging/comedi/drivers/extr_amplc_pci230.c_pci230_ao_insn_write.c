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
struct pci230_private {scalar_t__ daqio; int /*<<< orphan*/  ao_bipolar; } ;
struct comedi_subdevice {unsigned int* readback; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {struct pci230_private* private; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ PCI230_DACCON ; 
 int /*<<< orphan*/  comedi_range_is_bipolar (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  outw (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  pci230_ao_write_nofifo (struct comedi_device*,unsigned int,unsigned int) ; 

__attribute__((used)) static int pci230_ao_insn_write(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn,
				unsigned int *data)
{
	struct pci230_private *devpriv = dev->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int range = CR_RANGE(insn->chanspec);
	unsigned int val = s->readback[chan];
	int i;

	/*
	 * Set range - see analogue output range table; 0 => unipolar 10V,
	 * 1 => bipolar +/-10V range scale
	 */
	devpriv->ao_bipolar = comedi_range_is_bipolar(s, range);
	outw(range, devpriv->daqio + PCI230_DACCON);

	for (i = 0; i < insn->n; i++) {
		val = data[i];
		pci230_ao_write_nofifo(dev, val, chan);
	}
	s->readback[chan] = val;

	return insn->n;
}