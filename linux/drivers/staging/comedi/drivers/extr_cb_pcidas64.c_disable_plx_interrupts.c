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
struct pcidas64_private {scalar_t__ plx9080_iobase; scalar_t__ plx_intcsr_bits; } ;
struct comedi_device {struct pcidas64_private* private; } ;

/* Variables and functions */
 scalar_t__ PLX_REG_INTCSR ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void disable_plx_interrupts(struct comedi_device *dev)
{
	struct pcidas64_private *devpriv = dev->private;

	devpriv->plx_intcsr_bits = 0;
	writel(devpriv->plx_intcsr_bits,
	       devpriv->plx9080_iobase + PLX_REG_INTCSR);
}