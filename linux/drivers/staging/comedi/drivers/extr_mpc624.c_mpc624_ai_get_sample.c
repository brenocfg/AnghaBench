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
struct mpc624_private {unsigned int ai_speed; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; scalar_t__ iobase; struct mpc624_private* private; } ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 scalar_t__ MPC624_ADC ; 
 unsigned int MPC624_ADSCK ; 
 unsigned int MPC624_ADSDI ; 
 int MPC624_ADSDO ; 
 unsigned int MPC624_DMY_BIT ; 
 unsigned int MPC624_EOC_BIT ; 
 unsigned int MPC624_SGN_BIT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static unsigned int mpc624_ai_get_sample(struct comedi_device *dev,
					 struct comedi_subdevice *s)
{
	struct mpc624_private *devpriv = dev->private;
	unsigned int data_out = devpriv->ai_speed;
	unsigned int data_in = 0;
	unsigned int bit;
	int i;

	/* Start reading data */
	udelay(1);
	for (i = 0; i < 32; i++) {
		/* Set the clock low */
		outb(0, dev->iobase + MPC624_ADC);
		udelay(1);

		/* Set the ADSDI line for the next bit (send to MPC624) */
		bit = (data_out & BIT(31)) ? MPC624_ADSDI : 0;
		outb(bit, dev->iobase + MPC624_ADC);
		udelay(1);

		/* Set the clock high */
		outb(MPC624_ADSCK | bit, dev->iobase + MPC624_ADC);
		udelay(1);

		/* Read ADSDO on high clock (receive from MPC624) */
		data_in <<= 1;
		data_in |= (inb(dev->iobase + MPC624_ADC) & MPC624_ADSDO) >> 4;
		udelay(1);

		data_out <<= 1;
	}

	/*
	 * Received 32-bit long value consist of:
	 *	31: EOC - (End Of Transmission) bit - should be 0
	 *	30: DMY - (Dummy) bit - should be 0
	 *	29: SIG - (Sign) bit - 1 if positive, 0 if negative
	 *	28: MSB - (Most Significant Bit) - the first bit of the
	 *					   conversion result
	 *	....
	 *	05: LSB - (Least Significant Bit)- the last bit of the
	 *					   conversion result
	 *	04-00: sub-LSB - sub-LSBs are basically noise, but when
	 *			 averaged properly, they can increase
	 *			 conversion precision up to 29 bits;
	 *			 they can be discarded without loss of
	 *			 resolution.
	 */
	if (data_in & MPC624_EOC_BIT)
		dev_dbg(dev->class_dev, "EOC bit is set!");
	if (data_in & MPC624_DMY_BIT)
		dev_dbg(dev->class_dev, "DMY bit is set!");

	if (data_in & MPC624_SGN_BIT) {
		/*
		 * Voltage is positive
		 *
		 * comedi operates on unsigned numbers, so mask off EOC
		 * and DMY and don't clear the SGN bit
		 */
		data_in &= 0x3fffffff;
	} else {
		/*
		 * The voltage is negative
		 *
		 * data_in contains a number in 30-bit two's complement
		 * code and we must deal with it
		 */
		data_in |= MPC624_SGN_BIT;
		data_in = ~data_in;
		data_in += 1;
		/* clear EOC and DMY bits */
		data_in &= ~(MPC624_EOC_BIT | MPC624_DMY_BIT);
		data_in = 0x20000000 - data_in;
	}
	return data_in;
}