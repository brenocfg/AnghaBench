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
struct ni_private {int /*<<< orphan*/  counter_dev; } ;
struct comedi_device {struct ni_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ni_gpct_device_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mio_common_detach(struct comedi_device *dev)
{
	struct ni_private *devpriv = dev->private;

	if (devpriv)
		ni_gpct_device_destroy(devpriv->counter_dev);
}