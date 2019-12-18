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
struct dt282x_private {int adcsr; } ;
struct comedi_device {scalar_t__ iobase; struct dt282x_private* private; } ;

/* Variables and functions */
 unsigned int CR_CHAN (unsigned int) ; 
 unsigned int CR_RANGE (unsigned int) ; 
 int DT2821_ADCSR_CHAN (unsigned int) ; 
 int DT2821_ADCSR_GS (unsigned int) ; 
 scalar_t__ DT2821_ADCSR_REG ; 
 int DT2821_CHANCSR_LLE ; 
 int DT2821_CHANCSR_NUMB (int) ; 
 scalar_t__ DT2821_CHANCSR_REG ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static void dt282x_load_changain(struct comedi_device *dev, int n,
				 unsigned int *chanlist)
{
	struct dt282x_private *devpriv = dev->private;
	int i;

	outw(DT2821_CHANCSR_LLE | DT2821_CHANCSR_NUMB(n),
	     dev->iobase + DT2821_CHANCSR_REG);
	for (i = 0; i < n; i++) {
		unsigned int chan = CR_CHAN(chanlist[i]);
		unsigned int range = CR_RANGE(chanlist[i]);

		outw(devpriv->adcsr |
		     DT2821_ADCSR_GS(range) |
		     DT2821_ADCSR_CHAN(chan),
		     dev->iobase + DT2821_ADCSR_REG);
	}
	outw(DT2821_CHANCSR_NUMB(n), dev->iobase + DT2821_CHANCSR_REG);
}