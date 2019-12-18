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
struct ni_private {int /*<<< orphan*/  an_trig_etc_reg; } ;
struct comedi_device {struct ni_private* private; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NISTC_ATRIG_ETC_GPFO_0_ENA ; 
 int /*<<< orphan*/  NISTC_ATRIG_ETC_GPFO_1_ENA ; 
 int /*<<< orphan*/  NISTC_ATRIG_ETC_REG ; 
 int /*<<< orphan*/  ni_stc_writew (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ni_disable_gout_routing(unsigned int dest,
					  struct comedi_device *dev)
{
	struct ni_private *devpriv = dev->private;

	switch (dest) {
	case 0:
		devpriv->an_trig_etc_reg &= ~NISTC_ATRIG_ETC_GPFO_0_ENA;
		break;
	case 1:
		devpriv->an_trig_etc_reg &= ~NISTC_ATRIG_ETC_GPFO_1_ENA;
		break;
	default:
		return -EINVAL;
	}

	ni_stc_writew(dev, devpriv->an_trig_etc_reg, NISTC_ATRIG_ETC_REG);
	return 0;
}