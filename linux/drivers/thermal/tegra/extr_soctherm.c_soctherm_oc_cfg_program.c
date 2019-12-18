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
typedef  scalar_t__ u32 ;
struct tegra_soctherm {scalar_t__ regs; TYPE_1__* throt_cfgs; } ;
struct soctherm_oc_cfg {int mode; int active_low; int /*<<< orphan*/  intr_en; scalar_t__ alarm_filter; scalar_t__ alarm_cnt_thresh; scalar_t__ throt_period; } ;
typedef  enum soctherm_throttle_id { ____Placeholder_soctherm_throttle_id } soctherm_throttle_id ;
struct TYPE_2__ {struct soctherm_oc_cfg oc_cfg; } ;

/* Variables and functions */
 scalar_t__ ALARM_CFG (int) ; 
 scalar_t__ ALARM_CNT_THRESHOLD (int) ; 
 scalar_t__ ALARM_FILTER (int) ; 
 scalar_t__ ALARM_THROTTLE_PERIOD (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  OC1_CFG_ALARM_POLARITY_MASK ; 
 int /*<<< orphan*/  OC1_CFG_EN_THROTTLE_MASK ; 
 int /*<<< orphan*/  OC1_CFG_HW_RESTORE_MASK ; 
 int /*<<< orphan*/  OC1_CFG_THROTTLE_MODE_MASK ; 
 int OC_THROTTLE_MODE_DISABLED ; 
 scalar_t__ REG_SET_MASK (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  soctherm_oc_intr_enable (struct tegra_soctherm*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int soctherm_oc_cfg_program(struct tegra_soctherm *ts,
				      enum soctherm_throttle_id throt)
{
	u32 r;
	struct soctherm_oc_cfg *oc = &ts->throt_cfgs[throt].oc_cfg;

	if (oc->mode == OC_THROTTLE_MODE_DISABLED)
		return -EINVAL;

	r = REG_SET_MASK(0, OC1_CFG_HW_RESTORE_MASK, 1);
	r = REG_SET_MASK(r, OC1_CFG_THROTTLE_MODE_MASK, oc->mode);
	r = REG_SET_MASK(r, OC1_CFG_ALARM_POLARITY_MASK, oc->active_low);
	r = REG_SET_MASK(r, OC1_CFG_EN_THROTTLE_MASK, 1);
	writel(r, ts->regs + ALARM_CFG(throt));
	writel(oc->throt_period, ts->regs + ALARM_THROTTLE_PERIOD(throt));
	writel(oc->alarm_cnt_thresh, ts->regs + ALARM_CNT_THRESHOLD(throt));
	writel(oc->alarm_filter, ts->regs + ALARM_FILTER(throt));
	soctherm_oc_intr_enable(ts, throt, oc->intr_en);

	return 0;
}