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
struct tfp410_encoder {int dpms; TYPE_1__* mod; } ;
struct drm_encoder {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int DRM_MODE_DPMS_ON ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 struct tfp410_encoder* to_tfp410_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void tfp410_encoder_dpms(struct drm_encoder *encoder, int mode)
{
	struct tfp410_encoder *tfp410_encoder = to_tfp410_encoder(encoder);

	if (tfp410_encoder->dpms == mode)
		return;

	if (mode == DRM_MODE_DPMS_ON) {
		DBG("Power on");
		gpio_direction_output(tfp410_encoder->mod->gpio, 1);
	} else {
		DBG("Power off");
		gpio_direction_output(tfp410_encoder->mod->gpio, 0);
	}

	tfp410_encoder->dpms = mode;
}