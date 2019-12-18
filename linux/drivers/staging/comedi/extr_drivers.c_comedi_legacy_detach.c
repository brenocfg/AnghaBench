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
struct comedi_device {scalar_t__ iolen; scalar_t__ iobase; scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct comedi_device*) ; 
 int /*<<< orphan*/  release_region (scalar_t__,scalar_t__) ; 

void comedi_legacy_detach(struct comedi_device *dev)
{
	if (dev->irq) {
		free_irq(dev->irq, dev);
		dev->irq = 0;
	}
	if (dev->iobase && dev->iolen) {
		release_region(dev->iobase, dev->iolen);
		dev->iobase = 0;
		dev->iolen = 0;
	}
}