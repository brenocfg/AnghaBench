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
 scalar_t__ DAQP_PACER_HIGH_REG ; 
 scalar_t__ DAQP_PACER_LOW_REG ; 
 scalar_t__ DAQP_PACER_MID_REG ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 

__attribute__((used)) static void daqp_set_pacer(struct comedi_device *dev, unsigned int val)
{
	outb(val & 0xff, dev->iobase + DAQP_PACER_LOW_REG);
	outb((val >> 8) & 0xff, dev->iobase + DAQP_PACER_MID_REG);
	outb((val >> 16) & 0xff, dev->iobase + DAQP_PACER_HIGH_REG);
}