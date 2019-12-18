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
typedef  int u16 ;
struct dt9812_rmw_byte {int and_mask; int or_value; int /*<<< orphan*/  address; } ;
struct dt9812_private {int /*<<< orphan*/  mut; } ;
struct comedi_device {struct dt9812_private* private; } ;

/* Variables and functions */
 void* F020_MASK_DACXCN_DACXEN ; 
 int /*<<< orphan*/  F020_SFR_DAC0CN ; 
 int /*<<< orphan*/  F020_SFR_DAC0H ; 
 int /*<<< orphan*/  F020_SFR_DAC0L ; 
 int /*<<< orphan*/  F020_SFR_DAC1CN ; 
 int /*<<< orphan*/  F020_SFR_DAC1H ; 
 int /*<<< orphan*/  F020_SFR_DAC1L ; 
 int dt9812_rmw_multiple_registers (struct comedi_device*,int,struct dt9812_rmw_byte*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dt9812_analog_out(struct comedi_device *dev, int channel, u16 value)
{
	struct dt9812_private *devpriv = dev->private;
	struct dt9812_rmw_byte rmw[3];
	int ret;

	mutex_lock(&devpriv->mut);

	switch (channel) {
	case 0:
		/* 1. Set DAC mode */
		rmw[0].address = F020_SFR_DAC0CN;
		rmw[0].and_mask = 0xff;
		rmw[0].or_value = F020_MASK_DACXCN_DACXEN;

		/* 2. load lsb of DAC value first */
		rmw[1].address = F020_SFR_DAC0L;
		rmw[1].and_mask = 0xff;
		rmw[1].or_value = value & 0xff;

		/* 3. load msb of DAC value next to latch the 12-bit value */
		rmw[2].address = F020_SFR_DAC0H;
		rmw[2].and_mask = 0xff;
		rmw[2].or_value = (value >> 8) & 0xf;
		break;

	case 1:
		/* 1. Set DAC mode */
		rmw[0].address = F020_SFR_DAC1CN;
		rmw[0].and_mask = 0xff;
		rmw[0].or_value = F020_MASK_DACXCN_DACXEN;

		/* 2. load lsb of DAC value first */
		rmw[1].address = F020_SFR_DAC1L;
		rmw[1].and_mask = 0xff;
		rmw[1].or_value = value & 0xff;

		/* 3. load msb of DAC value next to latch the 12-bit value */
		rmw[2].address = F020_SFR_DAC1H;
		rmw[2].and_mask = 0xff;
		rmw[2].or_value = (value >> 8) & 0xf;
		break;
	}
	ret = dt9812_rmw_multiple_registers(dev, 3, rmw);

	mutex_unlock(&devpriv->mut);

	return ret;
}