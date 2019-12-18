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
struct ni_private {unsigned int ao_mode1; unsigned int ao_mode3; int /*<<< orphan*/  routing_tables; } ;
struct comedi_device {struct ni_private* private; } ;
struct comedi_cmd {scalar_t__ stop_src; scalar_t__ start_src; int start_arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_CHAN (int) ; 
 int CR_EDGE ; 
 int CR_INVERT ; 
 unsigned int NISTC_AO_MODE1_CONTINUOUS ; 
 int /*<<< orphan*/  NISTC_AO_MODE1_REG ; 
 unsigned int NISTC_AO_MODE1_TRIGGER_ONCE ; 
 int /*<<< orphan*/  NISTC_AO_MODE3_REG ; 
 unsigned int NISTC_AO_MODE3_TRIG_LEN ; 
 int /*<<< orphan*/  NISTC_AO_TRIG_SEL_REG ; 
 unsigned int NISTC_AO_TRIG_START1_EDGE ; 
 unsigned int NISTC_AO_TRIG_START1_POLARITY ; 
 unsigned int NISTC_AO_TRIG_START1_SEL (int /*<<< orphan*/ ) ; 
 unsigned int NISTC_AO_TRIG_START1_SYNC ; 
 unsigned int NISTC_RESET_AO_CFG_END ; 
 unsigned int NISTC_RESET_AO_CFG_START ; 
 int /*<<< orphan*/  NISTC_RESET_REG ; 
 int /*<<< orphan*/  NI_AO_StartTrigger ; 
 scalar_t__ TRIG_INT ; 
 scalar_t__ TRIG_NONE ; 
 int /*<<< orphan*/  ni_get_reg_value_roffs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ni_stc_writew (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ni_ao_cmd_set_trigger(struct comedi_device *dev,
				  const struct comedi_cmd *cmd)
{
	struct ni_private *devpriv = dev->private;
	unsigned int trigsel;

	ni_stc_writew(dev, NISTC_RESET_AO_CFG_START, NISTC_RESET_REG);

	/* sync */
	if (cmd->stop_src == TRIG_NONE) {
		devpriv->ao_mode1 |= NISTC_AO_MODE1_CONTINUOUS;
		devpriv->ao_mode1 &= ~NISTC_AO_MODE1_TRIGGER_ONCE;
	} else {
		devpriv->ao_mode1 &= ~NISTC_AO_MODE1_CONTINUOUS;
		devpriv->ao_mode1 |= NISTC_AO_MODE1_TRIGGER_ONCE;
	}
	ni_stc_writew(dev, devpriv->ao_mode1, NISTC_AO_MODE1_REG);

	if (cmd->start_src == TRIG_INT) {
		trigsel = NISTC_AO_TRIG_START1_EDGE |
			  NISTC_AO_TRIG_START1_SYNC;
	} else { /* TRIG_EXT */
		trigsel = NISTC_AO_TRIG_START1_SEL(
			ni_get_reg_value_roffs(CR_CHAN(cmd->start_arg),
					       NI_AO_StartTrigger,
					       &devpriv->routing_tables, 1));
		/* 0=active high, 1=active low. see daq-stc 3-24 (p186) */
		if (cmd->start_arg & CR_INVERT)
			trigsel |= NISTC_AO_TRIG_START1_POLARITY;
		/* 0=edge detection disabled, 1=enabled */
		if (cmd->start_arg & CR_EDGE)
			trigsel |= NISTC_AO_TRIG_START1_EDGE;
	}
	ni_stc_writew(dev, trigsel, NISTC_AO_TRIG_SEL_REG);

	/* AO_Delayed_START1 = 0, we do not support delayed start...yet */

	/* sync */
	/* select DA_START1 as PFI6/AO_START1 when configured as an output */
	devpriv->ao_mode3 &= ~NISTC_AO_MODE3_TRIG_LEN;
	ni_stc_writew(dev, devpriv->ao_mode3, NISTC_AO_MODE3_REG);

	ni_stc_writew(dev, NISTC_RESET_AO_CFG_END, NISTC_RESET_REG);
}