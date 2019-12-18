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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSS_CONTROL ; 
 int /*<<< orphan*/  DSS_PLL_CONTROL ; 
 int /*<<< orphan*/  DSS_REVISION ; 
 int /*<<< orphan*/  DSS_SDI_CONTROL ; 
 int /*<<< orphan*/  DSS_SDI_STATUS ; 
 int /*<<< orphan*/  DSS_SYSCONFIG ; 
 int /*<<< orphan*/  DSS_SYSSTATUS ; 
 int /*<<< orphan*/  DUMPREG (int /*<<< orphan*/ ) ; 
 int OMAP_DISPLAY_TYPE_SDI ; 
 int /*<<< orphan*/  OMAP_DSS_CHANNEL_LCD ; 
 int dss_feat_get_supported_displays (int /*<<< orphan*/ ) ; 
 scalar_t__ dss_runtime_get () ; 
 int /*<<< orphan*/  dss_runtime_put () ; 

__attribute__((used)) static void dss_dump_regs(struct seq_file *s)
{
#define DUMPREG(r) seq_printf(s, "%-35s %08x\n", #r, dss_read_reg(r))

	if (dss_runtime_get())
		return;

	DUMPREG(DSS_REVISION);
	DUMPREG(DSS_SYSCONFIG);
	DUMPREG(DSS_SYSSTATUS);
	DUMPREG(DSS_CONTROL);

	if (dss_feat_get_supported_displays(OMAP_DSS_CHANNEL_LCD) &
			OMAP_DISPLAY_TYPE_SDI) {
		DUMPREG(DSS_SDI_CONTROL);
		DUMPREG(DSS_PLL_CONTROL);
		DUMPREG(DSS_SDI_STATUS);
	}

	dss_runtime_put();
#undef DUMPREG
}