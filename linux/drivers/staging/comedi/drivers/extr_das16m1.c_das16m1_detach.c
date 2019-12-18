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
struct das16m1_private {int /*<<< orphan*/  counter; scalar_t__ extra_iobase; } ;
struct comedi_device {struct das16m1_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAS16M1_SIZE2 ; 
 int /*<<< orphan*/  comedi_legacy_detach (struct comedi_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void das16m1_detach(struct comedi_device *dev)
{
	struct das16m1_private *devpriv = dev->private;

	if (devpriv) {
		if (devpriv->extra_iobase)
			release_region(devpriv->extra_iobase, DAS16M1_SIZE2);
		kfree(devpriv->counter);
	}
	comedi_legacy_detach(dev);
}