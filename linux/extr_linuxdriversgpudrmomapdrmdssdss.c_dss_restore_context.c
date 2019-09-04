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
struct dss_device {TYPE_1__* feat; int /*<<< orphan*/  ctx_valid; } ;
struct TYPE_2__ {int* outputs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL ; 
 int /*<<< orphan*/  DSSDBG (char*) ; 
 size_t OMAP_DSS_CHANNEL_LCD ; 
 int OMAP_DSS_OUTPUT_SDI ; 
 int /*<<< orphan*/  PLL_CONTROL ; 
 int /*<<< orphan*/  RR (struct dss_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDI_CONTROL ; 

__attribute__((used)) static void dss_restore_context(struct dss_device *dss)
{
	DSSDBG("dss_restore_context\n");

	if (!dss->ctx_valid)
		return;

	RR(dss, CONTROL);

	if (dss->feat->outputs[OMAP_DSS_CHANNEL_LCD] & OMAP_DSS_OUTPUT_SDI) {
		RR(dss, SDI_CONTROL);
		RR(dss, PLL_CONTROL);
	}

	DSSDBG("context restored\n");
}