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
struct ni_private {int rtsi_trig_direction_reg; int rtsi_trig_b_output_reg; scalar_t__ is_m_series; } ;
struct comedi_device {struct ni_private* private; } ;

/* Variables and functions */
 int NISTC_RTSI_TRIGB_SUB_SEL1 ; 
 int NISTC_RTSI_TRIGB_SUB_SEL1_SHIFT ; 
 int NISTC_RTSI_TRIG_DIR_SUB_SEL1 ; 
 int NISTC_RTSI_TRIG_DIR_SUB_SEL1_SHIFT ; 

__attribute__((used)) static int get_rgout0_reg(struct comedi_device *dev)
{
	struct ni_private *devpriv = dev->private;
	int reg;

	if (devpriv->is_m_series)
		reg = (devpriv->rtsi_trig_direction_reg &
		       NISTC_RTSI_TRIG_DIR_SUB_SEL1)
		    >> NISTC_RTSI_TRIG_DIR_SUB_SEL1_SHIFT;
	else
		reg = (devpriv->rtsi_trig_b_output_reg &
		       NISTC_RTSI_TRIGB_SUB_SEL1)
		    >> NISTC_RTSI_TRIGB_SUB_SEL1_SHIFT;
	return reg;
}