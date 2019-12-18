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
struct tegra_soctherm {scalar_t__ regs; TYPE_1__* soc; struct soctherm_throt_cfg* throt_cfgs; } ;
struct soctherm_throt_cfg {scalar_t__ priority; int /*<<< orphan*/  init; } ;
typedef  enum soctherm_throttle_id { ____Placeholder_soctherm_throttle_id } soctherm_throttle_id ;
struct TYPE_2__ {scalar_t__ use_ccroc; } ;

/* Variables and functions */
 scalar_t__ REG_GET_MASK (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ REG_SET_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int THROTTLE_OC1 ; 
 scalar_t__ THROT_DELAY_CTRL (int) ; 
 int /*<<< orphan*/  THROT_DELAY_LITE_DELAY_MASK ; 
 scalar_t__ THROT_PRIORITY_CTRL (int) ; 
 int /*<<< orphan*/  THROT_PRIORITY_LITE_PRIO_MASK ; 
 scalar_t__ THROT_PRIORITY_LOCK ; 
 int /*<<< orphan*/  THROT_PRIORITY_LOCK_PRIORITY_MASK ; 
 scalar_t__ readl (scalar_t__) ; 
 scalar_t__ soctherm_oc_cfg_program (struct tegra_soctherm*,int) ; 
 int /*<<< orphan*/  throttlectl_cpu_level_select (struct tegra_soctherm*,int) ; 
 int /*<<< orphan*/  throttlectl_cpu_mn (struct tegra_soctherm*,int) ; 
 int /*<<< orphan*/  throttlectl_gpu_level_select (struct tegra_soctherm*,int) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void soctherm_throttle_program(struct tegra_soctherm *ts,
				      enum soctherm_throttle_id throt)
{
	u32 r;
	struct soctherm_throt_cfg stc = ts->throt_cfgs[throt];

	if (!stc.init)
		return;

	if ((throt >= THROTTLE_OC1) && (soctherm_oc_cfg_program(ts, throt)))
		return;

	/* Setup PSKIP parameters */
	if (ts->soc->use_ccroc)
		throttlectl_cpu_level_select(ts, throt);
	else
		throttlectl_cpu_mn(ts, throt);

	throttlectl_gpu_level_select(ts, throt);

	r = REG_SET_MASK(0, THROT_PRIORITY_LITE_PRIO_MASK, stc.priority);
	writel(r, ts->regs + THROT_PRIORITY_CTRL(throt));

	r = REG_SET_MASK(0, THROT_DELAY_LITE_DELAY_MASK, 0);
	writel(r, ts->regs + THROT_DELAY_CTRL(throt));

	r = readl(ts->regs + THROT_PRIORITY_LOCK);
	r = REG_GET_MASK(r, THROT_PRIORITY_LOCK_PRIORITY_MASK);
	if (r >= stc.priority)
		return;
	r = REG_SET_MASK(0, THROT_PRIORITY_LOCK_PRIORITY_MASK,
			 stc.priority);
	writel(r, ts->regs + THROT_PRIORITY_LOCK);
}