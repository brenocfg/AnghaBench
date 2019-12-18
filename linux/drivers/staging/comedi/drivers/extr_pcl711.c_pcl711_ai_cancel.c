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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCL711_INT_STAT_CLR ; 
 scalar_t__ PCL711_INT_STAT_REG ; 
 int /*<<< orphan*/  PCL711_MODE_SOFTTRIG ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pcl711_ai_set_mode (struct comedi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcl711_ai_cancel(struct comedi_device *dev,
			    struct comedi_subdevice *s)
{
	outb(PCL711_INT_STAT_CLR, dev->iobase + PCL711_INT_STAT_REG);
	pcl711_ai_set_mode(dev, PCL711_MODE_SOFTTRIG);
	return 0;
}