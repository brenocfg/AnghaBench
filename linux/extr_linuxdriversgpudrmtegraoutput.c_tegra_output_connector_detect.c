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
struct tegra_output {int hpd_gpio_flags; int /*<<< orphan*/  notifier; int /*<<< orphan*/  panel; int /*<<< orphan*/  hpd_gpio; } ;
struct drm_connector {int dummy; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int OF_GPIO_ACTIVE_LOW ; 
 int /*<<< orphan*/  cec_notifier_phys_addr_invalidate (int /*<<< orphan*/ ) ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 int connector_status_unknown ; 
 struct tegra_output* connector_to_output (struct drm_connector*) ; 
 scalar_t__ gpio_get_value (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 

enum drm_connector_status
tegra_output_connector_detect(struct drm_connector *connector, bool force)
{
	struct tegra_output *output = connector_to_output(connector);
	enum drm_connector_status status = connector_status_unknown;

	if (gpio_is_valid(output->hpd_gpio)) {
		if (output->hpd_gpio_flags & OF_GPIO_ACTIVE_LOW) {
			if (gpio_get_value(output->hpd_gpio) != 0)
				status = connector_status_disconnected;
			else
				status = connector_status_connected;
		} else {
			if (gpio_get_value(output->hpd_gpio) == 0)
				status = connector_status_disconnected;
			else
				status = connector_status_connected;
		}
	} else {
		if (!output->panel)
			status = connector_status_disconnected;
		else
			status = connector_status_connected;
	}

	if (status != connector_status_connected)
		cec_notifier_phys_addr_invalidate(output->notifier);

	return status;
}