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
struct comedi_device {struct cb_pcidda_private* private; } ;
struct cb_pcidda_private {scalar_t__ daqio; int /*<<< orphan*/  dac_cal1_bits; } ;

/* Variables and functions */
 scalar_t__ DACALIBRATION1 ; 
 int /*<<< orphan*/  SERIAL_IN_BIT ; 
 int /*<<< orphan*/  outw_p (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void cb_pcidda_serial_out(struct comedi_device *dev, unsigned int value,
				 unsigned int num_bits)
{
	struct cb_pcidda_private *devpriv = dev->private;
	int i;

	for (i = 1; i <= num_bits; i++) {
		/*  send bits most significant bit first */
		if (value & (1 << (num_bits - i)))
			devpriv->dac_cal1_bits |= SERIAL_IN_BIT;
		else
			devpriv->dac_cal1_bits &= ~SERIAL_IN_BIT;
		outw_p(devpriv->dac_cal1_bits, devpriv->daqio + DACALIBRATION1);
	}
}