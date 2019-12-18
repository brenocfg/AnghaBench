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
struct comedi_subdevice {unsigned int* readback; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ ATAO_AO_REG (unsigned int) ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atao_select_reg_group (struct comedi_device*,int) ; 
 int /*<<< orphan*/  comedi_offset_munge (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int atao_ao_insn_write(struct comedi_device *dev,
			      struct comedi_subdevice *s,
			      struct comedi_insn *insn,
			      unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int val = s->readback[chan];
	int i;

	if (chan == 0)
		atao_select_reg_group(dev, 1);

	for (i = 0; i < insn->n; i++) {
		val = data[i];

		/* the hardware expects two's complement values */
		outw(comedi_offset_munge(s, val),
		     dev->iobase + ATAO_AO_REG(chan));
	}
	s->readback[chan] = val;

	if (chan == 0)
		atao_select_reg_group(dev, 0);

	return insn->n;
}