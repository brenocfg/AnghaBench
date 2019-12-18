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
struct tegra_output {int /*<<< orphan*/  hpd_irq; scalar_t__ hpd_gpio; int /*<<< orphan*/  connector; scalar_t__ panel; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int drm_panel_attach (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 

int tegra_output_init(struct drm_device *drm, struct tegra_output *output)
{
	int err;

	if (output->panel) {
		err = drm_panel_attach(output->panel, &output->connector);
		if (err < 0)
			return err;
	}

	/*
	 * The connector is now registered and ready to receive hotplug events
	 * so the hotplug interrupt can be enabled.
	 */
	if (output->hpd_gpio)
		enable_irq(output->hpd_irq);

	return 0;
}