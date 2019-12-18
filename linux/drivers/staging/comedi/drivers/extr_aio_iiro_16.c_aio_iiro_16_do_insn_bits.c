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
 scalar_t__ AIO_IIRO_16_RELAY_0_7 ; 
 scalar_t__ AIO_IIRO_16_RELAY_8_15 ; 
 scalar_t__ comedi_dio_update_state (struct comedi_subdevice*,unsigned int*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int aio_iiro_16_do_insn_bits(struct comedi_device *dev,
				    struct comedi_subdevice *s,
				    struct comedi_insn *insn,
				    unsigned int *data)
{
	if (comedi_dio_update_state(s, data)) {
		outb(s->state & 0xff, dev->iobase + AIO_IIRO_16_RELAY_0_7);
		outb((s->state >> 8) & 0xff,
		     dev->iobase + AIO_IIRO_16_RELAY_8_15);
	}

	data[1] = s->state;

	return insn->n;
}