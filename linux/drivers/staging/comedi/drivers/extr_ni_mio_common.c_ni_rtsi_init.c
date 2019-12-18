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
struct ni_private {scalar_t__ rgout0_usage; int /*<<< orphan*/  rtsi_shared_mux_usage; scalar_t__ rtsi_shared_mux_reg; int /*<<< orphan*/  clock_and_fout2; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct ni_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_INPUT ; 
 int /*<<< orphan*/  NI_MIO_INTERNAL_CLOCK ; 
 int /*<<< orphan*/  NI_M_CLK_FOUT2_RTSI_10MHZ ; 
 int /*<<< orphan*/ * default_rtsi_routing ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ni_set_master_clock (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_set_rtsi_direction (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_set_rtsi_routing (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ith_rtsi_brd_reg (int,int /*<<< orphan*/ ,struct comedi_device*) ; 
 int /*<<< orphan*/  set_rgout0_reg (int /*<<< orphan*/ ,struct comedi_device*) ; 

__attribute__((used)) static void ni_rtsi_init(struct comedi_device *dev)
{
	struct ni_private *devpriv = dev->private;
	int i;

	/*  Initialises the RTSI bus signal switch to a default state */

	/*
	 * Use 10MHz instead of 20MHz for RTSI clock frequency. Appears
	 * to have no effect, at least on pxi-6281, which always uses
	 * 20MHz rtsi clock frequency
	 */
	devpriv->clock_and_fout2 = NI_M_CLK_FOUT2_RTSI_10MHZ;
	/*  Set clock mode to internal */
	if (ni_set_master_clock(dev, NI_MIO_INTERNAL_CLOCK, 0) < 0)
		dev_err(dev->class_dev, "ni_set_master_clock failed, bug?\n");

	/* default internal lines routing to RTSI bus lines */
	for (i = 0; i < 8; ++i) {
		ni_set_rtsi_direction(dev, i, COMEDI_INPUT);
		ni_set_rtsi_routing(dev, i, default_rtsi_routing[i]);
	}

	/*
	 * Sets the source and direction of the 4 on board lines.
	 * This configures all board lines to be:
	 * for e-series:
	 *   1) inputs (not sure what "output" would mean)
	 *   2) copying TRIGGER_LINE(0) (or RTSI0) output
	 * for m-series:
	 *   copying NI_PFI(0) output
	 */
	devpriv->rtsi_shared_mux_reg = 0;
	for (i = 0; i < 4; ++i)
		set_ith_rtsi_brd_reg(i, 0, dev);
	memset(devpriv->rtsi_shared_mux_usage, 0,
	       sizeof(devpriv->rtsi_shared_mux_usage));

	/* initialize rgout0 pin as unused. */
	devpriv->rgout0_usage = 0;
	set_rgout0_reg(0, dev);
}