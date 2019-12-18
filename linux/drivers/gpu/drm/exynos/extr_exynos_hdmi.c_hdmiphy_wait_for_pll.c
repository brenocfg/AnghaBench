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
struct hdmi_context {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  HDMI_PHY_STATUS ; 
 int HDMI_PHY_STATUS_READY ; 
 int hdmi_reg_read (struct hdmi_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void hdmiphy_wait_for_pll(struct hdmi_context *hdata)
{
	int tries;

	for (tries = 0; tries < 10; ++tries) {
		u32 val = hdmi_reg_read(hdata, HDMI_PHY_STATUS);

		if (val & HDMI_PHY_STATUS_READY) {
			DRM_DEV_DEBUG_KMS(hdata->dev,
					  "PLL stabilized after %d tries\n",
					  tries);
			return;
		}
		usleep_range(10, 20);
	}

	DRM_DEV_ERROR(hdata->dev, "PLL could not reach steady state\n");
}