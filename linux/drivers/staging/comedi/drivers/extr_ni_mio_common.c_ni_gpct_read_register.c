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
struct ni_gpct {TYPE_1__* counter_dev; } ;
struct comedi_device {int dummy; } ;
typedef  enum ni_gpct_register { ____Placeholder_ni_gpct_register } ni_gpct_register ;
struct TYPE_2__ {struct comedi_device* dev; } ;

/* Variables and functions */
#define  NITIO_G0_DMA_STATUS 133 
#define  NITIO_G0_HW_SAVE 132 
#define  NITIO_G0_SW_SAVE 131 
#define  NITIO_G1_DMA_STATUS 130 
#define  NITIO_G1_HW_SAVE 129 
#define  NITIO_G1_SW_SAVE 128 
 unsigned int ni_gpct_to_stc_register (struct comedi_device*,int) ; 
 unsigned int ni_readw (struct comedi_device*,unsigned int) ; 
 unsigned int ni_stc_readl (struct comedi_device*,unsigned int) ; 
 unsigned int ni_stc_readw (struct comedi_device*,unsigned int) ; 

__attribute__((used)) static unsigned int ni_gpct_read_register(struct ni_gpct *counter,
					  enum ni_gpct_register reg)
{
	struct comedi_device *dev = counter->counter_dev->dev;
	unsigned int stc_register = ni_gpct_to_stc_register(dev, reg);

	if (stc_register == 0)
		return 0;

	switch (reg) {
		/* m-series only registers */
	case NITIO_G0_DMA_STATUS:
	case NITIO_G1_DMA_STATUS:
		return ni_readw(dev, stc_register);

		/* 32 bit registers */
	case NITIO_G0_HW_SAVE:
	case NITIO_G1_HW_SAVE:
	case NITIO_G0_SW_SAVE:
	case NITIO_G1_SW_SAVE:
		return ni_stc_readl(dev, stc_register);

		/* 16 bit registers */
	default:
		return ni_stc_readw(dev, stc_register);
	}
}