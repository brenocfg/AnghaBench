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
 scalar_t__ DT2811_ADDATA_HI_REG ; 
 scalar_t__ DT2811_ADDATA_LO_REG ; 
 int inb (scalar_t__) ; 

__attribute__((used)) static unsigned int dt2811_ai_read_sample(struct comedi_device *dev,
					  struct comedi_subdevice *s)
{
	unsigned int val;

	val = inb(dev->iobase + DT2811_ADDATA_LO_REG) |
	      (inb(dev->iobase + DT2811_ADDATA_HI_REG) << 8);

	return val & s->maxdata;
}