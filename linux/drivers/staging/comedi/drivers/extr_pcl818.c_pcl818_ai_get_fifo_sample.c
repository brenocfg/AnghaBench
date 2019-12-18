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
struct comedi_subdevice {unsigned int maxdata; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ PCL818_FI_DATAHI ; 
 scalar_t__ PCL818_FI_DATALO ; 
 int inb (scalar_t__) ; 

__attribute__((used)) static unsigned int pcl818_ai_get_fifo_sample(struct comedi_device *dev,
					      struct comedi_subdevice *s,
					      unsigned int *chan)
{
	unsigned int val;

	val = inb(dev->iobase + PCL818_FI_DATALO);
	val |= (inb(dev->iobase + PCL818_FI_DATAHI) << 8);

	if (chan)
		*chan = val & 0xf;

	return (val >> 4) & s->maxdata;
}