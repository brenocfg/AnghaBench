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
struct ni_private {int /*<<< orphan*/  ao_mode3; } ;
struct comedi_device {struct ni_private* private; } ;
struct comedi_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NISTC_AO_MODE3_REG ; 
 int /*<<< orphan*/  NISTC_AO_MODE3_STOP_ON_OVERRUN_ERR ; 
 int /*<<< orphan*/  NISTC_RESET_AO_CFG_END ; 
 int /*<<< orphan*/  NISTC_RESET_AO_CFG_START ; 
 int /*<<< orphan*/  NISTC_RESET_REG ; 
 int /*<<< orphan*/  ni_stc_writew (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ni_ao_cmd_set_stop_conditions(struct comedi_device *dev,
					  const struct comedi_cmd *cmd)
{
	struct ni_private *devpriv = dev->private;

	ni_stc_writew(dev, NISTC_RESET_AO_CFG_START, NISTC_RESET_REG);

	devpriv->ao_mode3 |= NISTC_AO_MODE3_STOP_ON_OVERRUN_ERR;
	ni_stc_writew(dev, devpriv->ao_mode3, NISTC_AO_MODE3_REG);

	/*
	 * Since we are not supporting waveform staging, we ignore these errors:
	 * NISTC_AO_MODE3_STOP_ON_BC_TC_ERR,
	 * NISTC_AO_MODE3_STOP_ON_BC_TC_TRIG_ERR
	 */

	ni_stc_writew(dev, NISTC_RESET_AO_CFG_END, NISTC_RESET_REG);
}