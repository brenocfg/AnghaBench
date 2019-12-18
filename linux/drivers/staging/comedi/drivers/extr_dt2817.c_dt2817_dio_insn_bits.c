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
struct comedi_subdevice {int state; } ;
struct comedi_insn {int n; } ;
struct comedi_device {unsigned long iobase; } ;

/* Variables and functions */
 unsigned long DT2817_DATA ; 
 unsigned int comedi_dio_update_state (struct comedi_subdevice*,unsigned int*) ; 
 int inb (unsigned long) ; 
 int /*<<< orphan*/  outb (int,unsigned long) ; 

__attribute__((used)) static int dt2817_dio_insn_bits(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn,
				unsigned int *data)
{
	unsigned long iobase = dev->iobase + DT2817_DATA;
	unsigned int mask;
	unsigned int val;

	mask = comedi_dio_update_state(s, data);
	if (mask) {
		if (mask & 0x000000ff)
			outb(s->state & 0xff, iobase + 0);
		if (mask & 0x0000ff00)
			outb((s->state >> 8) & 0xff, iobase + 1);
		if (mask & 0x00ff0000)
			outb((s->state >> 16) & 0xff, iobase + 2);
		if (mask & 0xff000000)
			outb((s->state >> 24) & 0xff, iobase + 3);
	}

	val = inb(iobase + 0);
	val |= (inb(iobase + 1) << 8);
	val |= (inb(iobase + 2) << 16);
	val |= (inb(iobase + 3) << 24);

	data[1] = val;

	return insn->n;
}