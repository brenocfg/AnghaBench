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
struct dss_device {int ctx_valid; TYPE_1__* feat; } ;
struct TYPE_2__ {int* outputs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL ; 
 int /*<<< orphan*/  DSSDBG (char*) ; 
 size_t OMAP_DSS_CHANNEL_LCD ; 
 int OMAP_DSS_OUTPUT_SDI ; 
 int /*<<< orphan*/  PLL_CONTROL ; 
 int /*<<< orphan*/  SDI_CONTROL ; 
 int /*<<< orphan*/  SR (struct dss_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dss_save_context(struct dss_device *dss)
{
	DSSDBG("dss_save_context\n");

	SR(dss, CONTROL);

	if (dss->feat->outputs[OMAP_DSS_CHANNEL_LCD] & OMAP_DSS_OUTPUT_SDI) {
		SR(dss, SDI_CONTROL);
		SR(dss, PLL_CONTROL);
	}

	dss->ctx_valid = true;

	DSSDBG("context saved\n");
}