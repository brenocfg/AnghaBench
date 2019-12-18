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
struct pci_dev {int dummy; } ;
struct comedi_subdevice {int n_chan; int maxdata; unsigned int state; int /*<<< orphan*/  insn_bits; int /*<<< orphan*/ * range_table; void* subdev_flags; int /*<<< orphan*/  type; int /*<<< orphan*/  insn_write; } ;
struct comedi_device {scalar_t__ iobase; struct comedi_subdevice* subdevices; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_SUBD_AO ; 
 int /*<<< orphan*/  COMEDI_SUBD_DI ; 
 int /*<<< orphan*/  COMEDI_SUBD_DO ; 
 scalar_t__ PCI6208_DIO ; 
 unsigned int PCI6208_DIO_DO_MASK ; 
 unsigned int PCI6208_DIO_DO_SHIFT ; 
 void* SDF_READABLE ; 
 void* SDF_WRITABLE ; 
 int comedi_alloc_subdev_readback (struct comedi_subdevice*) ; 
 int comedi_alloc_subdevices (struct comedi_device*,int) ; 
 int comedi_pci_enable (struct comedi_device*) ; 
 struct pci_dev* comedi_to_pci_dev (struct comedi_device*) ; 
 unsigned int inw (scalar_t__) ; 
 int /*<<< orphan*/  pci6208_ao_insn_write ; 
 int /*<<< orphan*/  pci6208_di_insn_bits ; 
 int /*<<< orphan*/  pci6208_do_insn_bits ; 
 scalar_t__ pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  range_bipolar10 ; 
 int /*<<< orphan*/  range_digital ; 

__attribute__((used)) static int pci6208_auto_attach(struct comedi_device *dev,
			       unsigned long context_unused)
{
	struct pci_dev *pcidev = comedi_to_pci_dev(dev);
	struct comedi_subdevice *s;
	unsigned int val;
	int ret;

	ret = comedi_pci_enable(dev);
	if (ret)
		return ret;
	dev->iobase = pci_resource_start(pcidev, 2);

	ret = comedi_alloc_subdevices(dev, 3);
	if (ret)
		return ret;

	s = &dev->subdevices[0];
	/* analog output subdevice */
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 16;	/* Only 8 usable on PCI-6208 */
	s->maxdata	= 0xffff;
	s->range_table	= &range_bipolar10;
	s->insn_write	= pci6208_ao_insn_write;

	ret = comedi_alloc_subdev_readback(s);
	if (ret)
		return ret;

	s = &dev->subdevices[1];
	/* digital input subdevice */
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 4;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= pci6208_di_insn_bits;

	s = &dev->subdevices[2];
	/* digital output subdevice */
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 4;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= pci6208_do_insn_bits;

	/*
	 * Get the read back signals from the digital outputs
	 * and save it as the initial state for the subdevice.
	 */
	val = inw(dev->iobase + PCI6208_DIO);
	val = (val & PCI6208_DIO_DO_MASK) >> PCI6208_DIO_DO_SHIFT;
	s->state	= val;

	return 0;
}