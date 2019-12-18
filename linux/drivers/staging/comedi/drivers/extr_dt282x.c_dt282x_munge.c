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
struct dt282x_private {scalar_t__ ad_2scomp; } ;
struct comedi_subdevice {unsigned int maxdata; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct dt282x_private* private; } ;

/* Variables and functions */
 unsigned int comedi_offset_munge (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void dt282x_munge(struct comedi_device *dev,
			 struct comedi_subdevice *s,
			 unsigned short *buf,
			 unsigned int nbytes)
{
	struct dt282x_private *devpriv = dev->private;
	unsigned int val;
	int i;

	if (nbytes % 2)
		dev_err(dev->class_dev,
			"bug! odd number of bytes from dma xfer\n");

	for (i = 0; i < nbytes / 2; i++) {
		val = buf[i];
		val &= s->maxdata;
		if (devpriv->ad_2scomp)
			val = comedi_offset_munge(s, val);

		buf[i] = val;
	}
}