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
struct ni_private {scalar_t__ is_m_series; } ;
struct comedi_device {struct ni_private* private; } ;

/* Variables and functions */
 int NISTC_INTA2_ENA_REG ; 
 unsigned int NISTC_INTA_ENA_G0_GATE ; 
 int NISTC_INTB2_ENA_REG ; 
 unsigned int NISTC_INTB_ENA_G1_GATE ; 
 int /*<<< orphan*/  ni_stc_writew (struct comedi_device*,unsigned int,int) ; 

__attribute__((used)) static void ni_e_series_enable_second_irq(struct comedi_device *dev,
					  unsigned int gpct_index, short enable)
{
	struct ni_private *devpriv = dev->private;
	unsigned int val = 0;
	int reg;

	if (devpriv->is_m_series || gpct_index > 1)
		return;

	/*
	 * e-series boards use the second irq signals to generate
	 * dma requests for their counters
	 */
	if (gpct_index == 0) {
		reg = NISTC_INTA2_ENA_REG;
		if (enable)
			val = NISTC_INTA_ENA_G0_GATE;
	} else {
		reg = NISTC_INTB2_ENA_REG;
		if (enable)
			val = NISTC_INTB_ENA_G1_GATE;
	}
	ni_stc_writew(dev, val, reg);
}