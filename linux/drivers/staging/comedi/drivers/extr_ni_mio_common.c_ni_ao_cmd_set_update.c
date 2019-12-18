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
struct ni_private {int ao_mode1; int ao_cmd2; int ao_mode2; int ao_cmd1; int /*<<< orphan*/  routing_tables; } ;
struct comedi_device {struct ni_private* private; } ;
struct comedi_cmd {scalar_t__ scan_begin_src; int scan_begin_arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMDF_ROUND_NEAREST ; 
 int /*<<< orphan*/  CR_CHAN (int) ; 
 int CR_INVERT ; 
 int NISTC_AO_CMD1_DAC0_UPDATE_MODE ; 
 int NISTC_AO_CMD1_DAC1_UPDATE_MODE ; 
 int /*<<< orphan*/  NISTC_AO_CMD1_REG ; 
 int NISTC_AO_CMD1_UI_LOAD ; 
 int NISTC_AO_CMD2_BC_GATE_ENA ; 
 int /*<<< orphan*/  NISTC_AO_CMD2_REG ; 
 int /*<<< orphan*/  NISTC_AO_MODE1_REG ; 
 int NISTC_AO_MODE1_UI_SRC_MASK ; 
 int NISTC_AO_MODE1_UI_SRC_POLARITY ; 
 int NISTC_AO_MODE1_UPDATE_SRC (int /*<<< orphan*/ ) ; 
 int NISTC_AO_MODE1_UPDATE_SRC_MASK ; 
 int NISTC_AO_MODE1_UPDATE_SRC_POLARITY ; 
 int /*<<< orphan*/  NISTC_AO_MODE2_REG ; 
 int NISTC_AO_MODE2_UI_INIT_LOAD_SRC ; 
 int NISTC_AO_MODE2_UI_RELOAD_MODE (int) ; 
 int /*<<< orphan*/  NISTC_AO_UI_LOADA_REG ; 
 int NISTC_RESET_AO_CFG_END ; 
 int NISTC_RESET_AO_CFG_START ; 
 int /*<<< orphan*/  NISTC_RESET_REG ; 
 int /*<<< orphan*/  NI_AO_SampleClock ; 
 scalar_t__ TRIG_TIMER ; 
 int /*<<< orphan*/  ni_get_reg_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int ni_ns_to_timer (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_stc_writel (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_stc_writew (struct comedi_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ni_ao_cmd_set_update(struct comedi_device *dev,
				 const struct comedi_cmd *cmd)
{
	struct ni_private *devpriv = dev->private;

	ni_stc_writew(dev, NISTC_RESET_AO_CFG_START, NISTC_RESET_REG);

	/*
	 * zero out these bit fields to be set below. Does an ao-reset do this
	 * automatically?
	 */
	devpriv->ao_mode1 &= ~(
	  NISTC_AO_MODE1_UI_SRC_MASK         |
	  NISTC_AO_MODE1_UI_SRC_POLARITY     |
	  NISTC_AO_MODE1_UPDATE_SRC_MASK     |
	  NISTC_AO_MODE1_UPDATE_SRC_POLARITY
	);

	if (cmd->scan_begin_src == TRIG_TIMER) {
		unsigned int trigvar;

		devpriv->ao_cmd2  &= ~NISTC_AO_CMD2_BC_GATE_ENA;

		/*
		 * NOTE: there are several other ways of configuring internal
		 * updates, but we'll only support one for now:  using
		 * AO_IN_TIMEBASE, w/o waveform staging, w/o a delay between
		 * START1 and first update, and also w/o local buffer mode w/
		 * pauses.
		 */

		/*
		 * This is already done above:
		 * devpriv->ao_mode1 &= ~(
		 *   // set UPDATE_Source to UI_TC:
		 *   NISTC_AO_MODE1_UPDATE_SRC_MASK |
		 *   // set UPDATE_Source_Polarity to rising (required?)
		 *   NISTC_AO_MODE1_UPDATE_SRC_POLARITY |
		 *   // set UI_Source to AO_IN_TIMEBASE1:
		 *   NISTC_AO_MODE1_UI_SRC_MASK     |
		 *   // set UI_Source_Polarity to rising (required?)
		 *   NISTC_AO_MODE1_UI_SRC_POLARITY
		 * );
		 */

		/*
		 * TODO:  use ao_ui_clock_source to allow all possible signals
		 * to be routed to UI_Source_Select.  See tSTC.h for
		 * eseries/ni67xx and tMSeries.h for mseries.
		 */

		trigvar = ni_ns_to_timer(dev, cmd->scan_begin_arg,
					 CMDF_ROUND_NEAREST);

		/*
		 * Wait N TB3 ticks after the start trigger before
		 * clocking (N must be >=2).
		 */
		/* following line: 2-1 per STC */
		ni_stc_writel(dev, 1, NISTC_AO_UI_LOADA_REG);
		ni_stc_writew(dev, NISTC_AO_CMD1_UI_LOAD, NISTC_AO_CMD1_REG);
		ni_stc_writel(dev, trigvar, NISTC_AO_UI_LOADA_REG);
	} else { /* TRIG_EXT */
		/* FIXME:  assert scan_begin_arg != 0, ret failure otherwise */
		devpriv->ao_cmd2  |= NISTC_AO_CMD2_BC_GATE_ENA;
		devpriv->ao_mode1 |= NISTC_AO_MODE1_UPDATE_SRC(
			ni_get_reg_value(CR_CHAN(cmd->scan_begin_arg),
					 NI_AO_SampleClock,
					 &devpriv->routing_tables));
		if (cmd->scan_begin_arg & CR_INVERT)
			devpriv->ao_mode1 |= NISTC_AO_MODE1_UPDATE_SRC_POLARITY;
	}

	ni_stc_writew(dev, devpriv->ao_cmd2, NISTC_AO_CMD2_REG);
	ni_stc_writew(dev, devpriv->ao_mode1, NISTC_AO_MODE1_REG);
	devpriv->ao_mode2 &= ~(NISTC_AO_MODE2_UI_RELOAD_MODE(3) |
			       NISTC_AO_MODE2_UI_INIT_LOAD_SRC);
	ni_stc_writew(dev, devpriv->ao_mode2, NISTC_AO_MODE2_REG);

	/* Configure DAQ-STC for Timed update mode */
	devpriv->ao_cmd1 |= NISTC_AO_CMD1_DAC1_UPDATE_MODE |
			    NISTC_AO_CMD1_DAC0_UPDATE_MODE;
	/* We are not using UPDATE2-->don't have to set DACx_Source_Select */
	ni_stc_writew(dev, devpriv->ao_cmd1, NISTC_AO_CMD1_REG);

	ni_stc_writew(dev, NISTC_RESET_AO_CFG_END, NISTC_RESET_REG);
}