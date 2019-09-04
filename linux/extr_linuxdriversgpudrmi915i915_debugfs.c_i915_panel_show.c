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
struct seq_file {struct drm_connector* private; } ;
struct intel_dp {int /*<<< orphan*/  backlight_off_delay; int /*<<< orphan*/  backlight_on_delay; int /*<<< orphan*/  panel_power_down_delay; int /*<<< orphan*/  panel_power_up_delay; } ;
struct drm_connector {scalar_t__ status; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ connector_status_connected ; 
 struct intel_dp* enc_to_intel_dp (int /*<<< orphan*/ *) ; 
 TYPE_1__* intel_attached_encoder (struct drm_connector*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_panel_show(struct seq_file *m, void *data)
{
	struct drm_connector *connector = m->private;
	struct intel_dp *intel_dp =
		enc_to_intel_dp(&intel_attached_encoder(connector)->base);

	if (connector->status != connector_status_connected)
		return -ENODEV;

	seq_printf(m, "Panel power up delay: %d\n",
		   intel_dp->panel_power_up_delay);
	seq_printf(m, "Panel power down delay: %d\n",
		   intel_dp->panel_power_down_delay);
	seq_printf(m, "Backlight on delay: %d\n",
		   intel_dp->backlight_on_delay);
	seq_printf(m, "Backlight off delay: %d\n",
		   intel_dp->backlight_off_delay);

	return 0;
}