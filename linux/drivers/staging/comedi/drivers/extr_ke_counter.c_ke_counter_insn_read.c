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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ KE_LATCH_REG (unsigned int) ; 
 scalar_t__ KE_LSB_REG (unsigned int) ; 
 scalar_t__ KE_MID_REG (unsigned int) ; 
 scalar_t__ KE_MSB_REG (unsigned int) ; 
 scalar_t__ KE_SIGN_REG (unsigned int) ; 
 int inb (scalar_t__) ; 

__attribute__((used)) static int ke_counter_insn_read(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn,
				unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int val;
	int i;

	for (i = 0; i < insn->n; i++) {
		/* Order matters */
		inb(dev->iobase + KE_LATCH_REG(chan));

		val = inb(dev->iobase + KE_LSB_REG(chan));
		val |= (inb(dev->iobase + KE_MID_REG(chan)) << 8);
		val |= (inb(dev->iobase + KE_MSB_REG(chan)) << 16);
		val |= (inb(dev->iobase + KE_SIGN_REG(chan)) << 24);

		data[i] = val;
	}

	return insn->n;
}