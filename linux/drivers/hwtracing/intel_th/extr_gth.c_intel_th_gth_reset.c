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
typedef  int u32 ;
struct gth_device {scalar_t__ base; } ;

/* Variables and functions */
 int CTS_ACTION_CONTROL_SET_STATE (int /*<<< orphan*/ ) ; 
 int CTS_ACTION_CONTROL_TRIGGER ; 
 int CTS_EVENT_ENABLE_IF_ANYTHING ; 
 int /*<<< orphan*/  CTS_STATE_IDLE ; 
 int EBUSY ; 
 scalar_t__ GTH_NONE ; 
 scalar_t__ REG_CTS_C0S0_ACT ; 
 scalar_t__ REG_CTS_C0S0_EN ; 
 scalar_t__ REG_GTH_DESTOVR ; 
 scalar_t__ REG_GTH_SCR ; 
 scalar_t__ REG_GTH_SCR2 ; 
 scalar_t__ REG_GTH_SCRPD0 ; 
 scalar_t__ REG_GTH_SWDEST0 ; 
 int SCRPD_DEBUGGER_IN_USE ; 
 int SCRPD_STH_IS_ENABLED ; 
 int SCRPD_TRIGGER_IS_ENABLED ; 
 int /*<<< orphan*/  TH_OUTPUT_PARM (int) ; 
 scalar_t__ gth_output_parm_get (struct gth_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gth_output_set (struct gth_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gth_smcfreq_set (struct gth_device*,int,int) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static int intel_th_gth_reset(struct gth_device *gth)
{
	u32 reg;
	int port, i;

	reg = ioread32(gth->base + REG_GTH_SCRPD0);
	if (reg & SCRPD_DEBUGGER_IN_USE)
		return -EBUSY;

	/* Always save/restore STH and TU registers in S0ix entry/exit */
	reg |= SCRPD_STH_IS_ENABLED | SCRPD_TRIGGER_IS_ENABLED;
	iowrite32(reg, gth->base + REG_GTH_SCRPD0);

	/* output ports */
	for (port = 0; port < 8; port++) {
		if (gth_output_parm_get(gth, port, TH_OUTPUT_PARM(port)) ==
		    GTH_NONE)
			continue;

		gth_output_set(gth, port, 0);
		gth_smcfreq_set(gth, port, 16);
	}
	/* disable overrides */
	iowrite32(0, gth->base + REG_GTH_DESTOVR);

	/* masters swdest_0~31 and gswdest */
	for (i = 0; i < 33; i++)
		iowrite32(0, gth->base + REG_GTH_SWDEST0 + i * 4);

	/* sources */
	iowrite32(0, gth->base + REG_GTH_SCR);
	iowrite32(0xfc, gth->base + REG_GTH_SCR2);

	/* setup CTS for single trigger */
	iowrite32(CTS_EVENT_ENABLE_IF_ANYTHING, gth->base + REG_CTS_C0S0_EN);
	iowrite32(CTS_ACTION_CONTROL_SET_STATE(CTS_STATE_IDLE) |
		  CTS_ACTION_CONTROL_TRIGGER, gth->base + REG_CTS_C0S0_ACT);

	return 0;
}