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
struct ni_private {scalar_t__ is_m_series; int /*<<< orphan*/  ao_mode2; int /*<<< orphan*/  ao_mode1; } ;
struct comedi_device {struct ni_private* private; } ;
struct comedi_cmd {int stop_arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  NISTC_AO_BC_LOADA_REG ; 
 int /*<<< orphan*/  NISTC_AO_CMD1_BC_LOAD ; 
 int /*<<< orphan*/  NISTC_AO_CMD1_REG ; 
 int /*<<< orphan*/  NISTC_AO_CMD1_UC_LOAD ; 
 int /*<<< orphan*/  NISTC_AO_MODE1_REG ; 
 int /*<<< orphan*/  NISTC_AO_MODE2_BC_INIT_LOAD_SRC ; 
 int /*<<< orphan*/  NISTC_AO_MODE2_REG ; 
 int /*<<< orphan*/  NISTC_AO_MODE2_UC_INIT_LOAD_SRC ; 
 int /*<<< orphan*/  NISTC_AO_UC_LOADA_REG ; 
 int /*<<< orphan*/  NISTC_RESET_AO_CFG_END ; 
 int /*<<< orphan*/  NISTC_RESET_AO_CFG_START ; 
 int /*<<< orphan*/  NISTC_RESET_REG ; 
 int /*<<< orphan*/  ni_stc_writel (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_stc_writew (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ni_ao_cmd_set_counters(struct comedi_device *dev,
				   const struct comedi_cmd *cmd)
{
	struct ni_private *devpriv = dev->private;
	/* Not supporting 'waveform staging' or 'local buffer with pauses' */

	ni_stc_writew(dev, NISTC_RESET_AO_CFG_START, NISTC_RESET_REG);
	/*
	 * This relies on ao_mode1/(Trigger_Once | Continuous) being set in
	 * set_trigger above.  It is unclear whether we really need to re-write
	 * this register with these values.  The mhddk examples for e-series
	 * show writing this in both places, but the examples for m-series show
	 * a single write in the set_counters function (here).
	 */
	ni_stc_writew(dev, devpriv->ao_mode1, NISTC_AO_MODE1_REG);

	/* sync (upload number of buffer iterations -1) */
	/* indicate that we want to use BC_Load_A_Register as the source */
	devpriv->ao_mode2 &= ~NISTC_AO_MODE2_BC_INIT_LOAD_SRC;
	ni_stc_writew(dev, devpriv->ao_mode2, NISTC_AO_MODE2_REG);

	/*
	 * if the BC_TC interrupt is still issued in spite of UC, BC, UI
	 * ignoring BC_TC, then we will need to find a way to ignore that
	 * interrupt in continuous mode.
	 */
	ni_stc_writel(dev, 0, NISTC_AO_BC_LOADA_REG); /* iter once */

	/* sync (issue command to load number of buffer iterations -1) */
	ni_stc_writew(dev, NISTC_AO_CMD1_BC_LOAD, NISTC_AO_CMD1_REG);

	/* sync (upload number of updates in buffer) */
	/* indicate that we want to use UC_Load_A_Register as the source */
	devpriv->ao_mode2 &= ~NISTC_AO_MODE2_UC_INIT_LOAD_SRC;
	ni_stc_writew(dev, devpriv->ao_mode2, NISTC_AO_MODE2_REG);

	/*
	 * if a user specifies '0', this automatically assumes the entire 24bit
	 * address space is available for the (multiple iterations of single
	 * buffer) MISB.  Otherwise, stop_arg specifies the MISB length that
	 * will be used, regardless of whether we are in continuous mode or not.
	 * In continuous mode, the output will just iterate indefinitely over
	 * the MISB.
	 */
	{
		unsigned int stop_arg = cmd->stop_arg > 0 ?
			(cmd->stop_arg & 0xffffff) : 0xffffff;

		if (devpriv->is_m_series) {
			/*
			 * this is how the NI example code does it for m-series
			 * boards, verified correct with 6259
			 */
			ni_stc_writel(dev, stop_arg - 1, NISTC_AO_UC_LOADA_REG);

			/* sync (issue cmd to load number of updates in MISB) */
			ni_stc_writew(dev, NISTC_AO_CMD1_UC_LOAD,
				      NISTC_AO_CMD1_REG);
		} else {
			ni_stc_writel(dev, stop_arg, NISTC_AO_UC_LOADA_REG);

			/* sync (issue cmd to load number of updates in MISB) */
			ni_stc_writew(dev, NISTC_AO_CMD1_UC_LOAD,
				      NISTC_AO_CMD1_REG);

			/*
			 * sync (upload number of updates-1 in MISB)
			 * --eseries only?
			 */
			ni_stc_writel(dev, stop_arg - 1, NISTC_AO_UC_LOADA_REG);
		}
	}

	ni_stc_writew(dev, NISTC_RESET_AO_CFG_END, NISTC_RESET_REG);
}