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
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c6xdigio_pwm_write (struct comedi_device*,unsigned int,unsigned int) ; 

__attribute__((used)) static int c6xdigio_pwm_insn_write(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   struct comedi_insn *insn,
				   unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int val = (s->state >> (16 * chan)) & 0xffff;
	int i;

	for (i = 0; i < insn->n; i++) {
		val = data[i];
		c6xdigio_pwm_write(dev, chan, val);
	}

	/*
	 * There are only 2 PWM channels and they have a maxdata of 500.
	 * Instead of allocating private data to save the values in for
	 * readback this driver just packs the values for the two channels
	 * in the s->state.
	 */
	s->state &= (0xffff << (16 * chan));
	s->state |= (val << (16 * chan));

	return insn->n;
}