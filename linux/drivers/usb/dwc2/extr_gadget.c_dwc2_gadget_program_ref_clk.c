#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int ref_clk_per; int sof_cnt_wkup_alert; } ;
struct dwc2_hsotg {int /*<<< orphan*/  dev; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  GREFCLK ; 
 int GREFCLK_REFCLKPER_SHIFT ; 
 int GREFCLK_REF_CLK_MODE ; 
 int GREFCLK_SOF_CNT_WKUP_ALERT_SHIFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 

void dwc2_gadget_program_ref_clk(struct dwc2_hsotg *hsotg)
{
	u32 val = 0;

	val |= GREFCLK_REF_CLK_MODE;
	val |= hsotg->params.ref_clk_per << GREFCLK_REFCLKPER_SHIFT;
	val |= hsotg->params.sof_cnt_wkup_alert <<
	       GREFCLK_SOF_CNT_WKUP_ALERT_SHIFT;

	dwc2_writel(hsotg, val, GREFCLK);
	dev_dbg(hsotg->dev, "GREFCLK=0x%08x\n", dwc2_readl(hsotg, GREFCLK));
}