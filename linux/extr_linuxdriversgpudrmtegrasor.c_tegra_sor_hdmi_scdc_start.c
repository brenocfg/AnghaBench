#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_7__* crtc; } ;
struct drm_scdc {scalar_t__ supported; } ;
struct TYPE_8__ {struct drm_scdc scdc; } ;
struct TYPE_9__ {TYPE_1__ hdmi; } ;
struct TYPE_10__ {TYPE_2__ display_info; } ;
struct TYPE_11__ {TYPE_6__ encoder; TYPE_3__ connector; } ;
struct tegra_sor {int scdc_enabled; int /*<<< orphan*/  scdc; TYPE_4__ output; } ;
struct drm_display_mode {int clock; } ;
struct TYPE_14__ {TYPE_5__* state; } ;
struct TYPE_12__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_sor_hdmi_scdc_enable (struct tegra_sor*) ; 

__attribute__((used)) static void tegra_sor_hdmi_scdc_start(struct tegra_sor *sor)
{
	struct drm_scdc *scdc = &sor->output.connector.display_info.hdmi.scdc;
	struct drm_display_mode *mode;

	mode = &sor->output.encoder.crtc->state->adjusted_mode;

	if (mode->clock >= 340000 && scdc->supported) {
		schedule_delayed_work(&sor->scdc, msecs_to_jiffies(5000));
		tegra_sor_hdmi_scdc_enable(sor);
		sor->scdc_enabled = true;
	}
}