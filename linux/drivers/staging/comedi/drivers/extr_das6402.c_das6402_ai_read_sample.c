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
struct comedi_subdevice {int maxdata; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ DAS6402_AI_DATA_REG ; 
 unsigned int inw (scalar_t__) ; 

__attribute__((used)) static unsigned int das6402_ai_read_sample(struct comedi_device *dev,
					   struct comedi_subdevice *s)
{
	unsigned int val;

	val = inw(dev->iobase + DAS6402_AI_DATA_REG);
	if (s->maxdata == 0x0fff)
		val >>= 4;
	return val;
}