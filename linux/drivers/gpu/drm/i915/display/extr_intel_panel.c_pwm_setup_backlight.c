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
struct TYPE_4__ {int max; scalar_t__ level; int enabled; int /*<<< orphan*/ * pwm; scalar_t__ min; } ;
struct intel_panel {TYPE_2__ backlight; } ;
struct TYPE_3__ {struct drm_device* dev; } ;
struct intel_connector {struct intel_panel panel; TYPE_1__ base; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  CRC_PMIC_PWM_PERIOD_NS ; 
 scalar_t__ DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwm_apply_args (int /*<<< orphan*/ *) ; 
 int pwm_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pwm_get (int /*<<< orphan*/ ,char*) ; 
 int pwm_get_duty_cycle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwm_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pwm_setup_backlight(struct intel_connector *connector,
			       enum pipe pipe)
{
	struct drm_device *dev = connector->base.dev;
	struct intel_panel *panel = &connector->panel;
	int retval;

	/* Get the PWM chip for backlight control */
	panel->backlight.pwm = pwm_get(dev->dev, "pwm_backlight");
	if (IS_ERR(panel->backlight.pwm)) {
		DRM_ERROR("Failed to own the pwm chip\n");
		panel->backlight.pwm = NULL;
		return -ENODEV;
	}

	/*
	 * FIXME: pwm_apply_args() should be removed when switching to
	 * the atomic PWM API.
	 */
	pwm_apply_args(panel->backlight.pwm);

	retval = pwm_config(panel->backlight.pwm, CRC_PMIC_PWM_PERIOD_NS,
			    CRC_PMIC_PWM_PERIOD_NS);
	if (retval < 0) {
		DRM_ERROR("Failed to configure the pwm chip\n");
		pwm_put(panel->backlight.pwm);
		panel->backlight.pwm = NULL;
		return retval;
	}

	panel->backlight.min = 0; /* 0% */
	panel->backlight.max = 100; /* 100% */
	panel->backlight.level = DIV_ROUND_UP(
				 pwm_get_duty_cycle(panel->backlight.pwm) * 100,
				 CRC_PMIC_PWM_PERIOD_NS);
	panel->backlight.enabled = panel->backlight.level != 0;

	return 0;
}