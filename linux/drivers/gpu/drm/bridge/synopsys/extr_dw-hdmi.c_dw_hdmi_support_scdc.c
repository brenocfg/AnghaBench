#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  low_rates; int /*<<< orphan*/  supported; } ;
struct TYPE_8__ {TYPE_2__ scrambling; int /*<<< orphan*/  supported; } ;
struct TYPE_7__ {TYPE_4__ scdc; } ;
struct drm_display_info {int max_tmds_clock; TYPE_3__ hdmi; } ;
struct TYPE_5__ {struct drm_display_info display_info; } ;
struct dw_hdmi {int version; int /*<<< orphan*/  ddc; TYPE_1__ connector; } ;

/* Variables and functions */

__attribute__((used)) static bool dw_hdmi_support_scdc(struct dw_hdmi *hdmi)
{
	struct drm_display_info *display = &hdmi->connector.display_info;

	/* Completely disable SCDC support for older controllers */
	if (hdmi->version < 0x200a)
		return false;

	/* Disable if no DDC bus */
	if (!hdmi->ddc)
		return false;

	/* Disable if SCDC is not supported, or if an HF-VSDB block is absent */
	if (!display->hdmi.scdc.supported ||
	    !display->hdmi.scdc.scrambling.supported)
		return false;

	/*
	 * Disable if display only support low TMDS rates and scrambling
	 * for low rates is not supported either
	 */
	if (!display->hdmi.scdc.scrambling.low_rates &&
	    display->max_tmds_clock <= 340000)
		return false;

	return true;
}