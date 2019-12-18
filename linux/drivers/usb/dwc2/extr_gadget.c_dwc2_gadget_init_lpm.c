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
struct TYPE_2__ {int hird_threshold; scalar_t__ service_interval; scalar_t__ besl; scalar_t__ lpm_clock_gating; scalar_t__ hird_threshold_en; int /*<<< orphan*/  lpm; } ;
struct dwc2_hsotg {TYPE_1__ params; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GINTMSK2 ; 
 int /*<<< orphan*/  GINTMSK2_WKUP_ALERT_INT_MSK ; 
 int /*<<< orphan*/  GLPMCFG ; 
 int GLPMCFG_APPL1RES ; 
 int GLPMCFG_ENBESL ; 
 int GLPMCFG_ENBLSLPM ; 
 int GLPMCFG_HIRD_THRES_EN ; 
 int GLPMCFG_HIRD_THRES_SHIFT ; 
 int GLPMCFG_LPMCAP ; 
 int GLPMCFG_LPM_ACCEPT_CTRL_ISOC ; 
 int GLPMCFG_LPM_REJECT_CTRL_CONTROL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_set_bit (struct dwc2_hsotg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 

void dwc2_gadget_init_lpm(struct dwc2_hsotg *hsotg)
{
	u32 val;

	if (!hsotg->params.lpm)
		return;

	val = GLPMCFG_LPMCAP | GLPMCFG_APPL1RES;
	val |= hsotg->params.hird_threshold_en ? GLPMCFG_HIRD_THRES_EN : 0;
	val |= hsotg->params.lpm_clock_gating ? GLPMCFG_ENBLSLPM : 0;
	val |= hsotg->params.hird_threshold << GLPMCFG_HIRD_THRES_SHIFT;
	val |= hsotg->params.besl ? GLPMCFG_ENBESL : 0;
	val |= GLPMCFG_LPM_REJECT_CTRL_CONTROL;
	val |= GLPMCFG_LPM_ACCEPT_CTRL_ISOC;
	dwc2_writel(hsotg, val, GLPMCFG);
	dev_dbg(hsotg->dev, "GLPMCFG=0x%08x\n", dwc2_readl(hsotg, GLPMCFG));

	/* Unmask WKUP_ALERT Interrupt */
	if (hsotg->params.service_interval)
		dwc2_set_bit(hsotg, GINTMSK2, GINTMSK2_WKUP_ALERT_INT_MSK);
}