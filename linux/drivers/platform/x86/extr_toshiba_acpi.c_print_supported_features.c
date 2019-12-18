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
struct toshiba_acpi_dev {scalar_t__ cooling_method_supported; scalar_t__ wwan_supported; scalar_t__ usb_three_supported; scalar_t__ panel_power_on_supported; scalar_t__ kbd_function_keys_supported; scalar_t__ usb_sleep_music_supported; scalar_t__ usb_rapid_charge_supported; scalar_t__ usb_sleep_charge_supported; scalar_t__ accelerometer_supported; scalar_t__ eco_supported; scalar_t__ touchpad_supported; scalar_t__ kbd_illum_supported; scalar_t__ illumination_supported; scalar_t__ tr_backlight_supported; scalar_t__ fan_supported; scalar_t__ video_supported; scalar_t__ backlight_dev; scalar_t__ hotkey_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_cont (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static void print_supported_features(struct toshiba_acpi_dev *dev)
{
	pr_info("Supported laptop features:");

	if (dev->hotkey_dev)
		pr_cont(" hotkeys");
	if (dev->backlight_dev)
		pr_cont(" backlight");
	if (dev->video_supported)
		pr_cont(" video-out");
	if (dev->fan_supported)
		pr_cont(" fan");
	if (dev->tr_backlight_supported)
		pr_cont(" transflective-backlight");
	if (dev->illumination_supported)
		pr_cont(" illumination");
	if (dev->kbd_illum_supported)
		pr_cont(" keyboard-backlight");
	if (dev->touchpad_supported)
		pr_cont(" touchpad");
	if (dev->eco_supported)
		pr_cont(" eco-led");
	if (dev->accelerometer_supported)
		pr_cont(" accelerometer-axes");
	if (dev->usb_sleep_charge_supported)
		pr_cont(" usb-sleep-charge");
	if (dev->usb_rapid_charge_supported)
		pr_cont(" usb-rapid-charge");
	if (dev->usb_sleep_music_supported)
		pr_cont(" usb-sleep-music");
	if (dev->kbd_function_keys_supported)
		pr_cont(" special-function-keys");
	if (dev->panel_power_on_supported)
		pr_cont(" panel-power-on");
	if (dev->usb_three_supported)
		pr_cont(" usb3");
	if (dev->wwan_supported)
		pr_cont(" wwan");
	if (dev->cooling_method_supported)
		pr_cont(" cooling-method");

	pr_cont("\n");
}