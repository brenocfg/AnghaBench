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
struct ni6527_private {unsigned int filter_interval; } ;
struct comedi_device {scalar_t__ mmio; struct ni6527_private* private; } ;

/* Variables and functions */
 unsigned int NI6527_CLR_INTERVAL ; 
 scalar_t__ NI6527_CLR_REG ; 
 scalar_t__ NI6527_FILT_INTERVAL_REG (int) ; 
 int /*<<< orphan*/  writeb (unsigned int,scalar_t__) ; 

__attribute__((used)) static void ni6527_set_filter_interval(struct comedi_device *dev,
				       unsigned int val)
{
	struct ni6527_private *devpriv = dev->private;

	if (val != devpriv->filter_interval) {
		writeb(val & 0xff, dev->mmio + NI6527_FILT_INTERVAL_REG(0));
		writeb((val >> 8) & 0xff,
		       dev->mmio + NI6527_FILT_INTERVAL_REG(1));
		writeb((val >> 16) & 0x0f,
		       dev->mmio + NI6527_FILT_INTERVAL_REG(2));

		writeb(NI6527_CLR_INTERVAL, dev->mmio + NI6527_CLR_REG);

		devpriv->filter_interval = val;
	}
}