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
struct cb_pcidda_private {scalar_t__ daqio; } ;

/* Variables and functions */
 scalar_t__ DACALIBRATION1 ; 
 int SERIAL_OUT_BIT ; 
 int inw_p (scalar_t__) ; 

__attribute__((used)) static unsigned int cb_pcidda_serial_in(struct comedi_device *dev)
{
	struct cb_pcidda_private *devpriv = dev->private;
	unsigned int value = 0;
	int i;
	const int value_width = 16;	/*  number of bits wide values are */

	for (i = 1; i <= value_width; i++) {
		/*  read bits most significant bit first */
		if (inw_p(devpriv->daqio + DACALIBRATION1) & SERIAL_OUT_BIT)
			value |= 1 << (value_width - i);
	}

	return value;
}