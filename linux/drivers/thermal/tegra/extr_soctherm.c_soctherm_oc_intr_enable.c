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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_soctherm {scalar_t__ regs; } ;
typedef  enum soctherm_throttle_id { ____Placeholder_soctherm_throttle_id } soctherm_throttle_id ;

/* Variables and functions */
 scalar_t__ OC_INTR_ENABLE ; 
 int /*<<< orphan*/  OC_INTR_OC1_MASK ; 
 int /*<<< orphan*/  OC_INTR_OC2_MASK ; 
 int /*<<< orphan*/  OC_INTR_OC3_MASK ; 
 int /*<<< orphan*/  OC_INTR_OC4_MASK ; 
 int /*<<< orphan*/  REG_SET_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
#define  THROTTLE_OC1 131 
#define  THROTTLE_OC2 130 
#define  THROTTLE_OC3 129 
#define  THROTTLE_OC4 128 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void soctherm_oc_intr_enable(struct tegra_soctherm *ts,
				    enum soctherm_throttle_id alarm,
				    bool enable)
{
	u32 r;

	if (!enable)
		return;

	r = readl(ts->regs + OC_INTR_ENABLE);
	switch (alarm) {
	case THROTTLE_OC1:
		r = REG_SET_MASK(r, OC_INTR_OC1_MASK, 1);
		break;
	case THROTTLE_OC2:
		r = REG_SET_MASK(r, OC_INTR_OC2_MASK, 1);
		break;
	case THROTTLE_OC3:
		r = REG_SET_MASK(r, OC_INTR_OC3_MASK, 1);
		break;
	case THROTTLE_OC4:
		r = REG_SET_MASK(r, OC_INTR_OC4_MASK, 1);
		break;
	default:
		r = 0;
		break;
	}
	writel(r, ts->regs + OC_INTR_ENABLE);
}