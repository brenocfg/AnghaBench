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
struct voltagedomain {int /*<<< orphan*/  (* write ) (scalar_t__,int /*<<< orphan*/ ) ;} ;
struct omap3_vc_timings {scalar_t__ voltsetup2; scalar_t__ voltsetup1; } ;
struct TYPE_2__ {scalar_t__ voltctrl; scalar_t__ voltsetup1; scalar_t__ voltsetup2; struct omap3_vc_timings* timings; struct voltagedomain* vd; } ;

/* Variables and functions */
 scalar_t__ OMAP3430_PRM_VOLTCTRL_AUTO_OFF ; 
 scalar_t__ OMAP3430_PRM_VOLTCTRL_AUTO_RET ; 
 scalar_t__ OMAP3430_PRM_VOLTCTRL_AUTO_SLEEP ; 
 scalar_t__ OMAP3430_PRM_VOLTCTRL_SEL_OFF ; 
 int /*<<< orphan*/  OMAP3_PRM_VOLTCTRL_OFFSET ; 
 int /*<<< orphan*/  OMAP3_PRM_VOLTSETUP1_OFFSET ; 
 int /*<<< orphan*/  OMAP3_PRM_VOLTSETUP2_OFFSET ; 
#define  PWRDM_POWER_OFF 129 
#define  PWRDM_POWER_RET 128 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__ vc ; 

void omap3_vc_set_pmic_signaling(int core_next_state)
{
	struct voltagedomain *vd = vc.vd;
	struct omap3_vc_timings *c = vc.timings;
	u32 voltctrl, voltsetup1, voltsetup2;

	voltctrl = vc.voltctrl;
	voltsetup1 = vc.voltsetup1;
	voltsetup2 = vc.voltsetup2;

	switch (core_next_state) {
	case PWRDM_POWER_OFF:
		voltctrl &= ~(OMAP3430_PRM_VOLTCTRL_AUTO_RET |
			      OMAP3430_PRM_VOLTCTRL_AUTO_SLEEP);
		voltctrl |= OMAP3430_PRM_VOLTCTRL_AUTO_OFF;
		if (voltctrl & OMAP3430_PRM_VOLTCTRL_SEL_OFF)
			voltsetup2 = c->voltsetup2;
		else
			voltsetup1 = c->voltsetup1;
		break;
	case PWRDM_POWER_RET:
	default:
		c++;
		voltctrl &= ~(OMAP3430_PRM_VOLTCTRL_AUTO_OFF |
			      OMAP3430_PRM_VOLTCTRL_AUTO_SLEEP);
		voltctrl |= OMAP3430_PRM_VOLTCTRL_AUTO_RET;
		voltsetup1 = c->voltsetup1;
		break;
	}

	if (voltctrl != vc.voltctrl) {
		vd->write(voltctrl, OMAP3_PRM_VOLTCTRL_OFFSET);
		vc.voltctrl = voltctrl;
	}
	if (voltsetup1 != vc.voltsetup1) {
		vd->write(c->voltsetup1,
			  OMAP3_PRM_VOLTSETUP1_OFFSET);
		vc.voltsetup1 = voltsetup1;
	}
	if (voltsetup2 != vc.voltsetup2) {
		vd->write(c->voltsetup2,
			  OMAP3_PRM_VOLTSETUP2_OFFSET);
		vc.voltsetup2 = voltsetup2;
	}
}