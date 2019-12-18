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
 int /*<<< orphan*/  apci1032_reset (struct comedi_device*) ; 
 int /*<<< orphan*/  comedi_pci_detach (struct comedi_device*) ; 

__attribute__((used)) static void apci1032_detach(struct comedi_device *dev)
{
	if (dev->iobase)
		apci1032_reset(dev);
	comedi_pci_detach(dev);
}