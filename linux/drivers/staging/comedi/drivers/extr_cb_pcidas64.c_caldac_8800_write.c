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
typedef  unsigned int u8 ;
struct pcidas64_private {scalar_t__ main_iobase; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct pcidas64_private* private; } ;

/* Variables and functions */
 scalar_t__ CALIBRATION_REG ; 
 unsigned int SELECT_8800_BIT ; 
 unsigned int SERIAL_CLOCK_BIT ; 
 unsigned int SERIAL_DATA_IN_BIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int const) ; 
 int /*<<< orphan*/  writew (unsigned int,scalar_t__) ; 

__attribute__((used)) static int caldac_8800_write(struct comedi_device *dev, unsigned int address,
			     u8 value)
{
	struct pcidas64_private *devpriv = dev->private;
	static const int num_caldac_channels = 8;
	static const int bitstream_length = 11;
	unsigned int bitstream = ((address & 0x7) << 8) | value;
	unsigned int bit, register_bits;
	static const int caldac_8800_udelay = 1;

	if (address >= num_caldac_channels) {
		dev_err(dev->class_dev, "illegal caldac channel\n");
		return -1;
	}
	for (bit = 1 << (bitstream_length - 1); bit; bit >>= 1) {
		register_bits = 0;
		if (bitstream & bit)
			register_bits |= SERIAL_DATA_IN_BIT;
		udelay(caldac_8800_udelay);
		writew(register_bits, devpriv->main_iobase + CALIBRATION_REG);
		register_bits |= SERIAL_CLOCK_BIT;
		udelay(caldac_8800_udelay);
		writew(register_bits, devpriv->main_iobase + CALIBRATION_REG);
	}
	udelay(caldac_8800_udelay);
	writew(SELECT_8800_BIT, devpriv->main_iobase + CALIBRATION_REG);
	udelay(caldac_8800_udelay);
	writew(0, devpriv->main_iobase + CALIBRATION_REG);
	udelay(caldac_8800_udelay);
	return 0;
}