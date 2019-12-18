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
struct comedi_subdevice {int n_chan; scalar_t__ private; } ;
struct comedi_insn {int n; } ;
struct comedi_device {unsigned long iobase; } ;

/* Variables and functions */
 int inb (unsigned long) ; 

__attribute__((used)) static int pci_dio_insn_bits_di_b(struct comedi_device *dev,
				  struct comedi_subdevice *s,
				  struct comedi_insn *insn,
				  unsigned int *data)
{
	unsigned long reg = (unsigned long)s->private;
	unsigned long iobase = dev->iobase + reg;

	data[1] = inb(iobase);
	if (s->n_chan > 8)
		data[1] |= (inb(iobase + 1) << 8);
	if (s->n_chan > 16)
		data[1] |= (inb(iobase + 2) << 16);
	if (s->n_chan > 24)
		data[1] |= (inb(iobase + 3) << 24);

	return insn->n;
}