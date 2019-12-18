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
struct comedi_device {scalar_t__ iobase; struct atmio16d_private* private; } ;
struct atmio16d_private {scalar_t__ adc_coding; } ;

/* Variables and functions */
 scalar_t__ AD_FIFO_REG ; 
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ MUX_GAIN_REG ; 
 scalar_t__ START_CONVERT_REG ; 
 scalar_t__ adc_2comp ; 
 int /*<<< orphan*/  atmio16d_ai_eoc ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static int atmio16d_ai_insn_read(struct comedi_device *dev,
				 struct comedi_subdevice *s,
				 struct comedi_insn *insn, unsigned int *data)
{
	struct atmio16d_private *devpriv = dev->private;
	int i;
	int chan;
	int gain;
	int ret;

	chan = CR_CHAN(insn->chanspec);
	gain = CR_RANGE(insn->chanspec);

	/* reset the Analog input circuitry */
	/* outw( 0, dev->iobase+AD_CLEAR_REG ); */
	/* reset the Analog Input MUX Counter to 0 */
	/* outw( 0, dev->iobase+MUX_CNTR_REG ); */

	/* set the Input MUX gain */
	outw(chan | (gain << 6), dev->iobase + MUX_GAIN_REG);

	for (i = 0; i < insn->n; i++) {
		/* start the conversion */
		outw(0, dev->iobase + START_CONVERT_REG);

		/* wait for it to finish */
		ret = comedi_timeout(dev, s, insn, atmio16d_ai_eoc, 0);
		if (ret)
			return ret;

		/* read the data now */
		data[i] = inw(dev->iobase + AD_FIFO_REG);
		/* change to two's complement if need be */
		if (devpriv->adc_coding == adc_2comp)
			data[i] ^= 0x800;
	}

	return i;
}