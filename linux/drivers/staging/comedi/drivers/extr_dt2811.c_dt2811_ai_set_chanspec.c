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
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned int CR_CHAN (unsigned int) ; 
 unsigned int CR_RANGE (unsigned int) ; 
 int DT2811_ADGCR_CHAN (unsigned int) ; 
 int DT2811_ADGCR_GAIN (unsigned int) ; 
 scalar_t__ DT2811_ADGCR_REG ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void dt2811_ai_set_chanspec(struct comedi_device *dev,
				   unsigned int chanspec)
{
	unsigned int chan = CR_CHAN(chanspec);
	unsigned int range = CR_RANGE(chanspec);

	outb(DT2811_ADGCR_CHAN(chan) | DT2811_ADGCR_GAIN(range),
	     dev->iobase + DT2811_ADGCR_REG);
}