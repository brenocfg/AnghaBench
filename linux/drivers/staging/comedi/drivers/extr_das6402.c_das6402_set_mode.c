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
 unsigned int DAS6402_MODE_ENHANCED ; 
 scalar_t__ DAS6402_MODE_REG ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 

__attribute__((used)) static void das6402_set_mode(struct comedi_device *dev,
			     unsigned int mode)
{
	outb(DAS6402_MODE_ENHANCED | mode, dev->iobase + DAS6402_MODE_REG);
}