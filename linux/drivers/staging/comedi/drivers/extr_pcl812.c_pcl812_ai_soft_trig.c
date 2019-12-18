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
 scalar_t__ PCL812_SOFTTRIG_REG ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void pcl812_ai_soft_trig(struct comedi_device *dev)
{
	/* writing any value triggers a software conversion */
	outb(255, dev->iobase + PCL812_SOFTTRIG_REG);
}