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
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ ME4000_DIO_PORT_0_REG ; 
 scalar_t__ ME4000_DIO_PORT_1_REG ; 
 scalar_t__ ME4000_DIO_PORT_2_REG ; 
 scalar_t__ ME4000_DIO_PORT_3_REG ; 
 scalar_t__ comedi_dio_update_state (struct comedi_subdevice*,unsigned int*) ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

__attribute__((used)) static int me4000_dio_insn_bits(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn,
				unsigned int *data)
{
	if (comedi_dio_update_state(s, data)) {
		outl((s->state >> 0) & 0xFF,
		     dev->iobase + ME4000_DIO_PORT_0_REG);
		outl((s->state >> 8) & 0xFF,
		     dev->iobase + ME4000_DIO_PORT_1_REG);
		outl((s->state >> 16) & 0xFF,
		     dev->iobase + ME4000_DIO_PORT_2_REG);
		outl((s->state >> 24) & 0xFF,
		     dev->iobase + ME4000_DIO_PORT_3_REG);
	}

	data[1] = ((inl(dev->iobase + ME4000_DIO_PORT_0_REG) & 0xFF) << 0) |
		  ((inl(dev->iobase + ME4000_DIO_PORT_1_REG) & 0xFF) << 8) |
		  ((inl(dev->iobase + ME4000_DIO_PORT_2_REG) & 0xFF) << 16) |
		  ((inl(dev->iobase + ME4000_DIO_PORT_3_REG) & 0xFF) << 24);

	return insn->n;
}