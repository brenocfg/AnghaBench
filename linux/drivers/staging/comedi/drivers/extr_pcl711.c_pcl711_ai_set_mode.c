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
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 unsigned int PCL711_MODE_EXT_IRQ ; 
 unsigned int PCL711_MODE_IRQ (int /*<<< orphan*/ ) ; 
 unsigned int PCL711_MODE_PACER_IRQ ; 
 scalar_t__ PCL711_MODE_REG ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 

__attribute__((used)) static void pcl711_ai_set_mode(struct comedi_device *dev, unsigned int mode)
{
	/*
	 * The pcl711b board uses bits in the mode register to select the
	 * interrupt. The other boards supported by this driver all use
	 * jumpers on the board.
	 *
	 * Enables the interrupt when needed on the pcl711b board. These
	 * bits do nothing on the other boards.
	 */
	if (mode == PCL711_MODE_EXT_IRQ || mode == PCL711_MODE_PACER_IRQ)
		mode |= PCL711_MODE_IRQ(dev->irq);

	outb(mode, dev->iobase + PCL711_MODE_REG);
}