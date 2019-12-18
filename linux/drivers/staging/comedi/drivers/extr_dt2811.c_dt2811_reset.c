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
 int DT2811_ADCSR_ADMODE (int /*<<< orphan*/ ) ; 
 int DT2811_ADCSR_CLRERROR ; 
 scalar_t__ DT2811_ADCSR_REG ; 
 scalar_t__ DT2811_ADDATA_HI_REG ; 
 scalar_t__ DT2811_ADDATA_LO_REG ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void dt2811_reset(struct comedi_device *dev)
{
	/* This is the initialization sequence from the users manual */
	outb(DT2811_ADCSR_ADMODE(0), dev->iobase + DT2811_ADCSR_REG);
	usleep_range(100, 1000);
	inb(dev->iobase + DT2811_ADDATA_LO_REG);
	inb(dev->iobase + DT2811_ADDATA_HI_REG);
	outb(DT2811_ADCSR_ADMODE(0) | DT2811_ADCSR_CLRERROR,
	     dev->iobase + DT2811_ADCSR_REG);
}