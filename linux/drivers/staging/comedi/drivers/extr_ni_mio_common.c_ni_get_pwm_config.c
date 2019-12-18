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
struct ni_private {unsigned int pwm_up_count; unsigned int clock_ns; unsigned int pwm_down_count; } ;
struct comedi_device {struct ni_private* private; } ;

/* Variables and functions */

__attribute__((used)) static int ni_get_pwm_config(struct comedi_device *dev, unsigned int *data)
{
	struct ni_private *devpriv = dev->private;

	data[1] = devpriv->pwm_up_count * devpriv->clock_ns;
	data[2] = devpriv->pwm_down_count * devpriv->clock_ns;
	return 3;
}