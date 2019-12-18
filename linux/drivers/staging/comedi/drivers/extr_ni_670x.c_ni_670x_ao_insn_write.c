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
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ AO_CHAN_OFFSET ; 
 scalar_t__ AO_VALUE_OFFSET ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int ni_670x_ao_insn_write(struct comedi_device *dev,
				 struct comedi_subdevice *s,
				 struct comedi_insn *insn,
				 unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int val = s->readback[chan];
	int i;

	/*
	 * Channel number mapping:
	 *
	 * NI 6703/ NI 6704 | NI 6704 Only
	 * -------------------------------
	 * vch(0)  :  0     | ich(16) :  1
	 * vch(1)  :  2     | ich(17) :  3
	 * ...              | ...
	 * vch(15) : 30     | ich(31) : 31
	 */
	for (i = 0; i < insn->n; i++) {
		val = data[i];
		/* First write in channel register which channel to use */
		writel(((chan & 15) << 1) | ((chan & 16) >> 4),
		       dev->mmio + AO_CHAN_OFFSET);
		/* write channel value */
		writel(val, dev->mmio + AO_VALUE_OFFSET);
	}
	s->readback[chan] = val;

	return insn->n;
}