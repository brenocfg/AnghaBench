#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct panel_encoder {TYPE_1__* mod; } ;
struct gpio_desc {int dummy; } ;
struct drm_encoder {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  power; } ;
struct backlight_device {TYPE_2__ props; } ;
struct TYPE_3__ {struct gpio_desc* enable_gpio; struct backlight_device* backlight; } ;

/* Variables and functions */
 int DRM_MODE_DPMS_ON ; 
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (struct gpio_desc*,int) ; 
 struct panel_encoder* to_panel_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void panel_encoder_dpms(struct drm_encoder *encoder, int mode)
{
	struct panel_encoder *panel_encoder = to_panel_encoder(encoder);
	struct backlight_device *backlight = panel_encoder->mod->backlight;
	struct gpio_desc *gpio = panel_encoder->mod->enable_gpio;

	if (backlight) {
		backlight->props.power = mode == DRM_MODE_DPMS_ON ?
					 FB_BLANK_UNBLANK : FB_BLANK_POWERDOWN;
		backlight_update_status(backlight);
	}

	if (gpio)
		gpiod_set_value_cansleep(gpio,
					 mode == DRM_MODE_DPMS_ON ? 1 : 0);
}