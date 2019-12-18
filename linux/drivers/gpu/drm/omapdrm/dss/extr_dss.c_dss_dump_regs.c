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
struct seq_file {struct dss_device* private; } ;
struct dss_device {TYPE_1__* feat; } ;
struct TYPE_2__ {int* outputs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSS_CONTROL ; 
 int /*<<< orphan*/  DSS_PLL_CONTROL ; 
 int /*<<< orphan*/  DSS_REVISION ; 
 int /*<<< orphan*/  DSS_SDI_CONTROL ; 
 int /*<<< orphan*/  DSS_SDI_STATUS ; 
 int /*<<< orphan*/  DSS_SYSCONFIG ; 
 int /*<<< orphan*/  DSS_SYSSTATUS ; 
 int /*<<< orphan*/  DUMPREG (struct dss_device*,int /*<<< orphan*/ ) ; 
 size_t OMAP_DSS_CHANNEL_LCD ; 
 int OMAP_DSS_OUTPUT_SDI ; 
 scalar_t__ dss_runtime_get (struct dss_device*) ; 
 int /*<<< orphan*/  dss_runtime_put (struct dss_device*) ; 

__attribute__((used)) static int dss_dump_regs(struct seq_file *s, void *p)
{
	struct dss_device *dss = s->private;

#define DUMPREG(dss, r) seq_printf(s, "%-35s %08x\n", #r, dss_read_reg(dss, r))

	if (dss_runtime_get(dss))
		return 0;

	DUMPREG(dss, DSS_REVISION);
	DUMPREG(dss, DSS_SYSCONFIG);
	DUMPREG(dss, DSS_SYSSTATUS);
	DUMPREG(dss, DSS_CONTROL);

	if (dss->feat->outputs[OMAP_DSS_CHANNEL_LCD] & OMAP_DSS_OUTPUT_SDI) {
		DUMPREG(dss, DSS_SDI_CONTROL);
		DUMPREG(dss, DSS_PLL_CONTROL);
		DUMPREG(dss, DSS_SDI_STATUS);
	}

	dss_runtime_put(dss);
#undef DUMPREG
	return 0;
}