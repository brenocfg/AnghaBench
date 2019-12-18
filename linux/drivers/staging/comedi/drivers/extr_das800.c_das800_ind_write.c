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
 scalar_t__ DAS800_GAIN ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 

__attribute__((used)) static void das800_ind_write(struct comedi_device *dev,
			     unsigned int val, unsigned int reg)
{
	/*
	 * Select dev->iobase + 2 to be desired register
	 * then write to that register.
	 */
	outb(reg, dev->iobase + DAS800_GAIN);
	outb(val, dev->iobase + 2);
}