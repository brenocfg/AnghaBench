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
struct comedi_device {struct apci1564_private* private; } ;
struct apci1564_private {unsigned long counters; } ;

/* Variables and functions */
 scalar_t__ ADDI_TCW_VAL_REG ; 
 unsigned long APCI1564_COUNTER (unsigned int) ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int inl (scalar_t__) ; 

__attribute__((used)) static int apci1564_counter_insn_read(struct comedi_device *dev,
				      struct comedi_subdevice *s,
				      struct comedi_insn *insn,
				      unsigned int *data)
{
	struct apci1564_private *devpriv = dev->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned long iobase = devpriv->counters + APCI1564_COUNTER(chan);
	int i;

	/* return the actual value of the counter */
	for (i = 0; i < insn->n; i++)
		data[i] = inl(iobase + ADDI_TCW_VAL_REG);

	return insn->n;
}