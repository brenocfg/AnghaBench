#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usbdux_private {int pwm_buf_sz; TYPE_1__* pwm_urb; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct usbdux_private* private; } ;
struct TYPE_2__ {scalar_t__ transfer_buffer; } ;

/* Variables and functions */

__attribute__((used)) static void usbdux_pwm_pattern(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       unsigned int chan,
			       unsigned int value,
			       unsigned int sign)
{
	struct usbdux_private *devpriv = dev->private;
	char pwm_mask = (1 << chan);	/* DIO bit for the PWM data */
	char sgn_mask = (16 << chan);	/* DIO bit for the sign */
	char *buf = (char *)(devpriv->pwm_urb->transfer_buffer);
	int szbuf = devpriv->pwm_buf_sz;
	int i;

	for (i = 0; i < szbuf; i++) {
		char c = *buf;

		c &= ~pwm_mask;
		if (i < value)
			c |= pwm_mask;
		if (!sign)
			c &= ~sgn_mask;
		else
			c |= sgn_mask;
		*buf++ = c;
	}
}