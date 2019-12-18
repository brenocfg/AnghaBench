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
struct das08_private_struct {int /*<<< orphan*/ * pg_gainlist; int /*<<< orphan*/  do_mux_bits; } ;
struct das08_board_struct {int ai_nbits; scalar_t__ ai_encoding; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; scalar_t__ iobase; int /*<<< orphan*/  spinlock; struct das08_private_struct* private; struct das08_board_struct* board_ptr; } ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ DAS08_AI_LSB_REG ; 
 scalar_t__ DAS08_AI_MSB_REG ; 
 scalar_t__ DAS08_AI_TRIG_REG ; 
 int /*<<< orphan*/  DAS08_CONTROL_MUX (int) ; 
 int /*<<< orphan*/  DAS08_CONTROL_MUX_MASK ; 
 scalar_t__ DAS08_CONTROL_REG ; 
 scalar_t__ DAS08_GAIN_REG ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  das08_ai_eoc ; 
 scalar_t__ das08_encode12 ; 
 scalar_t__ das08_encode16 ; 
 scalar_t__ das08_pcm_encode12 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outb_p (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int das08_ai_insn_read(struct comedi_device *dev,
			      struct comedi_subdevice *s,
			      struct comedi_insn *insn, unsigned int *data)
{
	const struct das08_board_struct *board = dev->board_ptr;
	struct das08_private_struct *devpriv = dev->private;
	int n;
	int chan;
	int range;
	int lsb, msb;
	int ret;

	chan = CR_CHAN(insn->chanspec);
	range = CR_RANGE(insn->chanspec);

	/* clear crap */
	inb(dev->iobase + DAS08_AI_LSB_REG);
	inb(dev->iobase + DAS08_AI_MSB_REG);

	/* set multiplexer */
	/* lock to prevent race with digital output */
	spin_lock(&dev->spinlock);
	devpriv->do_mux_bits &= ~DAS08_CONTROL_MUX_MASK;
	devpriv->do_mux_bits |= DAS08_CONTROL_MUX(chan);
	outb(devpriv->do_mux_bits, dev->iobase + DAS08_CONTROL_REG);
	spin_unlock(&dev->spinlock);

	if (devpriv->pg_gainlist) {
		/* set gain/range */
		range = CR_RANGE(insn->chanspec);
		outb(devpriv->pg_gainlist[range],
		     dev->iobase + DAS08_GAIN_REG);
	}

	for (n = 0; n < insn->n; n++) {
		/* clear over-range bits for 16-bit boards */
		if (board->ai_nbits == 16)
			if (inb(dev->iobase + DAS08_AI_MSB_REG) & 0x80)
				dev_info(dev->class_dev, "over-range\n");

		/* trigger conversion */
		outb_p(0, dev->iobase + DAS08_AI_TRIG_REG);

		ret = comedi_timeout(dev, s, insn, das08_ai_eoc, 0);
		if (ret)
			return ret;

		msb = inb(dev->iobase + DAS08_AI_MSB_REG);
		lsb = inb(dev->iobase + DAS08_AI_LSB_REG);
		if (board->ai_encoding == das08_encode12) {
			data[n] = (lsb >> 4) | (msb << 4);
		} else if (board->ai_encoding == das08_pcm_encode12) {
			data[n] = (msb << 8) + lsb;
		} else if (board->ai_encoding == das08_encode16) {
			/*
			 * "JR" 16-bit boards are sign-magnitude.
			 *
			 * XXX The manual seems to imply that 0 is full-scale
			 * negative and 65535 is full-scale positive, but the
			 * original COMEDI patch to add support for the
			 * DAS08/JR/16 and DAS08/JR/16-AO boards have it
			 * encoded as sign-magnitude.  Assume the original
			 * COMEDI code is correct for now.
			 */
			unsigned int magnitude = lsb | ((msb & 0x7f) << 8);

			/*
			 * MSB bit 7 is 0 for negative, 1 for positive voltage.
			 * COMEDI 16-bit bipolar data value for 0V is 0x8000.
			 */
			if (msb & 0x80)
				data[n] = BIT(15) + magnitude;
			else
				data[n] = BIT(15) - magnitude;
		} else {
			dev_err(dev->class_dev, "bug! unknown ai encoding\n");
			return -1;
		}
	}

	return n;
}