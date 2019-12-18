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
struct ni_private {scalar_t__ is_6xxx; scalar_t__ ao_mode3; scalar_t__ is_m_series; scalar_t__ ao_mode2; scalar_t__ ao_mode1; scalar_t__ ao_cmd2; scalar_t__ ao_cmd1; } ;
struct comedi_subdevice {unsigned int n_chan; } ;
struct comedi_device {struct ni_private* private; } ;

/* Variables and functions */
 unsigned int NI611X_AO_MISC_CLEAR_WG ; 
 int /*<<< orphan*/  NI611X_AO_MISC_REG ; 
 int /*<<< orphan*/  NI671X_AO_IMMEDIATE_REG ; 
 scalar_t__ NISTC_AO_CMD1_DISARM ; 
 int /*<<< orphan*/  NISTC_AO_CMD1_REG ; 
 int /*<<< orphan*/  NISTC_AO_CMD2_REG ; 
 int /*<<< orphan*/  NISTC_AO_MODE1_REG ; 
 int /*<<< orphan*/  NISTC_AO_MODE2_REG ; 
 scalar_t__ NISTC_AO_MODE3_LAST_GATE_DISABLE ; 
 int /*<<< orphan*/  NISTC_AO_MODE3_REG ; 
 int /*<<< orphan*/  NISTC_AO_OUT_CTRL_REG ; 
 scalar_t__ NISTC_AO_PERSONAL_BC_SRC_SEL ; 
 int /*<<< orphan*/  NISTC_AO_PERSONAL_REG ; 
 int /*<<< orphan*/  NISTC_AO_START_SEL_REG ; 
 int /*<<< orphan*/  NISTC_AO_TRIG_SEL_REG ; 
 scalar_t__ NISTC_INTB_ACK_AO_ALL ; 
 int /*<<< orphan*/  NISTC_INTB_ACK_REG ; 
 int /*<<< orphan*/  NISTC_INTB_ENA_REG ; 
 scalar_t__ NISTC_RESET_AO ; 
 scalar_t__ NISTC_RESET_AO_CFG_END ; 
 scalar_t__ NISTC_RESET_AO_CFG_START ; 
 int /*<<< orphan*/  NISTC_RESET_REG ; 
 int /*<<< orphan*/  ni_ao_win_outw (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_release_ao_mite_channel (struct comedi_device*) ; 
 int /*<<< orphan*/  ni_set_bits (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_stc_writew (struct comedi_device*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_ao_reset(struct comedi_device *dev, struct comedi_subdevice *s)
{
	/* See 3.6.1.2 "Resetting", of DAQ-STC Technical Reference Manual */

	/*
	 * In the following, the "--sync" comments are meant to denote
	 * asynchronous boundaries for setting the registers as described in the
	 * DAQ-STC mostly in the order also described in the DAQ-STC.
	 */

	struct ni_private *devpriv = dev->private;

	ni_release_ao_mite_channel(dev);

	/* --sync (reset AO) */
	if (devpriv->is_m_series)
		/* following example in mhddk for m-series */
		ni_stc_writew(dev, NISTC_RESET_AO, NISTC_RESET_REG);

	/*--sync (start config) */
	ni_stc_writew(dev, NISTC_RESET_AO_CFG_START, NISTC_RESET_REG);

	/*--sync (Disarm) */
	ni_stc_writew(dev, NISTC_AO_CMD1_DISARM, NISTC_AO_CMD1_REG);

	/*
	 * --sync
	 * (clear bunch of registers--mseries mhddk examples do not include
	 * this)
	 */
	devpriv->ao_cmd1  = 0;
	devpriv->ao_cmd2  = 0;
	devpriv->ao_mode1 = 0;
	devpriv->ao_mode2 = 0;
	if (devpriv->is_m_series)
		devpriv->ao_mode3 = NISTC_AO_MODE3_LAST_GATE_DISABLE;
	else
		devpriv->ao_mode3 = 0;

	ni_stc_writew(dev, 0, NISTC_AO_PERSONAL_REG);
	ni_stc_writew(dev, 0, NISTC_AO_CMD1_REG);
	ni_stc_writew(dev, 0, NISTC_AO_CMD2_REG);
	ni_stc_writew(dev, 0, NISTC_AO_MODE1_REG);
	ni_stc_writew(dev, 0, NISTC_AO_MODE2_REG);
	ni_stc_writew(dev, 0, NISTC_AO_OUT_CTRL_REG);
	ni_stc_writew(dev, devpriv->ao_mode3, NISTC_AO_MODE3_REG);
	ni_stc_writew(dev, 0, NISTC_AO_START_SEL_REG);
	ni_stc_writew(dev, 0, NISTC_AO_TRIG_SEL_REG);

	/*--sync (disable interrupts) */
	ni_set_bits(dev, NISTC_INTB_ENA_REG, ~0, 0);

	/*--sync (ack) */
	ni_stc_writew(dev, NISTC_AO_PERSONAL_BC_SRC_SEL, NISTC_AO_PERSONAL_REG);
	ni_stc_writew(dev, NISTC_INTB_ACK_AO_ALL, NISTC_INTB_ACK_REG);

	/*--not in DAQ-STC.  which doc? */
	if (devpriv->is_6xxx) {
		ni_ao_win_outw(dev, (1u << s->n_chan) - 1u,
			       NI671X_AO_IMMEDIATE_REG);
		ni_ao_win_outw(dev, NI611X_AO_MISC_CLEAR_WG,
			       NI611X_AO_MISC_REG);
	}
	ni_stc_writew(dev, NISTC_RESET_AO_CFG_END, NISTC_RESET_REG);
	/*--end */

	return 0;
}