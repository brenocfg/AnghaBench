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
struct db2k_private {scalar_t__ plx; } ;
struct comedi_device {struct db2k_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_pci_detach (struct comedi_device*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 

__attribute__((used)) static void db2k_detach(struct comedi_device *dev)
{
	struct db2k_private *devpriv = dev->private;

	if (devpriv && devpriv->plx)
		iounmap(devpriv->plx);
	comedi_pci_detach(dev);
}