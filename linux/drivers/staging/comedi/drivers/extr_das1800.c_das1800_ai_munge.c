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
struct das1800_private {scalar_t__ ai_is_unipolar; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct das1800_private* private; } ;

/* Variables and functions */
 unsigned int comedi_bytes_to_samples (struct comedi_subdevice*,unsigned int) ; 
 unsigned short comedi_offset_munge (struct comedi_subdevice*,unsigned short) ; 

__attribute__((used)) static void das1800_ai_munge(struct comedi_device *dev,
			     struct comedi_subdevice *s,
			     void *data, unsigned int num_bytes,
			     unsigned int start_chan_index)
{
	struct das1800_private *devpriv = dev->private;
	unsigned short *array = data;
	unsigned int num_samples = comedi_bytes_to_samples(s, num_bytes);
	unsigned int i;

	if (devpriv->ai_is_unipolar)
		return;

	for (i = 0; i < num_samples; i++)
		array[i] = comedi_offset_munge(s, array[i]);
}