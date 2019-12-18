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
struct dwc2_qtd {scalar_t__ error_count; } ;
struct dwc2_hsotg {int /*<<< orphan*/  dev; } ;
struct dwc2_host_chan {scalar_t__ ep_is_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCINTMSK_DATATGLERR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  disable_hc_int (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_hc_handle_tt_clear (struct dwc2_hsotg*,struct dwc2_host_chan*,struct dwc2_qtd*) ; 

__attribute__((used)) static void dwc2_hc_datatglerr_intr(struct dwc2_hsotg *hsotg,
				    struct dwc2_host_chan *chan, int chnum,
				    struct dwc2_qtd *qtd)
{
	dev_dbg(hsotg->dev,
		"--Host Channel %d Interrupt: Data Toggle Error--\n", chnum);

	if (chan->ep_is_in)
		qtd->error_count = 0;
	else
		dev_err(hsotg->dev,
			"Data Toggle Error on OUT transfer, channel %d\n",
			chnum);

	dwc2_hc_handle_tt_clear(hsotg, chan, qtd);
	disable_hc_int(hsotg, chnum, HCINTMSK_DATATGLERR);
}