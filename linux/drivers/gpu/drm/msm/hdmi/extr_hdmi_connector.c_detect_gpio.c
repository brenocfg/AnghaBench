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
struct hdmi_platform_config {struct hdmi_gpio_data* gpios; } ;
struct hdmi_gpio_data {int /*<<< orphan*/  gpiod; } ;
struct hdmi {struct hdmi_platform_config* config; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 size_t HPD_GPIO_INDEX ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 scalar_t__ gpiod_get_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum drm_connector_status detect_gpio(struct hdmi *hdmi)
{
	const struct hdmi_platform_config *config = hdmi->config;
	struct hdmi_gpio_data hpd_gpio = config->gpios[HPD_GPIO_INDEX];

	return gpiod_get_value(hpd_gpio.gpiod) ?
			connector_status_connected :
			connector_status_disconnected;
}