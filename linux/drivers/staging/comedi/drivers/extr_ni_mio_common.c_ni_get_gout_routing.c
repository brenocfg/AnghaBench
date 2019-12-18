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
struct ni_private {unsigned int an_trig_etc_reg; } ;
struct comedi_device {struct ni_private* private; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int NISTC_ATRIG_ETC_GPFO_0_ENA ; 
 int NISTC_ATRIG_ETC_GPFO_0_SEL_TO_SRC (unsigned int) ; 
 unsigned int NISTC_ATRIG_ETC_GPFO_1_ENA ; 
 int NISTC_ATRIG_ETC_GPFO_1_SEL_TO_SRC (unsigned int) ; 

__attribute__((used)) static inline int ni_get_gout_routing(unsigned int dest,
				      struct comedi_device *dev)
{
	struct ni_private *devpriv = dev->private;
	unsigned int reg = devpriv->an_trig_etc_reg;

	switch (dest) {
	case 0:
		if (reg & NISTC_ATRIG_ETC_GPFO_0_ENA)
			return NISTC_ATRIG_ETC_GPFO_0_SEL_TO_SRC(reg);
		break;
	case 1:
		if (reg & NISTC_ATRIG_ETC_GPFO_1_ENA)
			return NISTC_ATRIG_ETC_GPFO_1_SEL_TO_SRC(reg);
		break;
	}

	return -EINVAL;
}