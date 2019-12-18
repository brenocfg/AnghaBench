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
struct comedi_device {struct cb_pcidda_private* private; } ;
struct cb_pcidda_private {unsigned int* ao_range; unsigned int* eeprom_data; } ;

/* Variables and functions */
 scalar_t__ CB_DDA_CALDAC_COURSE_GAIN ; 
 scalar_t__ CB_DDA_CALDAC_COURSE_OFFSET ; 
 scalar_t__ CB_DDA_CALDAC_FINE_GAIN ; 
 scalar_t__ CB_DDA_CALDAC_FINE_OFFSET ; 
 int /*<<< orphan*/  cb_pcidda_write_caldac (struct comedi_device*,unsigned int,scalar_t__,unsigned int) ; 

__attribute__((used)) static void cb_pcidda_calibrate(struct comedi_device *dev, unsigned int channel,
				unsigned int range)
{
	struct cb_pcidda_private *devpriv = dev->private;
	unsigned int caldac = channel / 2;	/* two caldacs per channel */
	unsigned int chan = 4 * (channel % 2);	/* caldac channel base */
	unsigned int index = 2 * range + 12 * channel;
	unsigned int offset;
	unsigned int gain;

	/* save range so we can tell when we need to readjust calibration */
	devpriv->ao_range[channel] = range;

	/* get values from eeprom data */
	offset = devpriv->eeprom_data[0x7 + index];
	gain = devpriv->eeprom_data[0x8 + index];

	/* set caldacs */
	cb_pcidda_write_caldac(dev, caldac, chan + CB_DDA_CALDAC_COURSE_OFFSET,
			       (offset >> 8) & 0xff);
	cb_pcidda_write_caldac(dev, caldac, chan + CB_DDA_CALDAC_FINE_OFFSET,
			       offset & 0xff);
	cb_pcidda_write_caldac(dev, caldac, chan + CB_DDA_CALDAC_COURSE_GAIN,
			       (gain >> 8) & 0xff);
	cb_pcidda_write_caldac(dev, caldac, chan + CB_DDA_CALDAC_FINE_GAIN,
			       gain & 0xff);
}