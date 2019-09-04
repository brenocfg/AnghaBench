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
struct v4l2_flash {int /*<<< orphan*/ * iled_cdev; TYPE_1__* fled_cdev; struct v4l2_ctrl** ctrls; } ;
struct v4l2_ctrl {int val; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;
struct TYPE_2__ {int /*<<< orphan*/  led_cdev; } ;

/* Variables and functions */
 size_t LED_MODE ; 
 size_t TORCH_INTENSITY ; 
 scalar_t__ V4L2_FLASH_LED_MODE_TORCH ; 
 int __intensity_to_led_brightness (struct v4l2_ctrl*,int) ; 
 void* call_flash_op (struct v4l2_flash*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ has_flash_op (struct v4l2_flash*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intensity_to_led_brightness ; 
 int /*<<< orphan*/  led_brightness_to_intensity ; 
 int /*<<< orphan*/  led_set_brightness_sync (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void v4l2_flash_set_led_brightness(struct v4l2_flash *v4l2_flash,
					struct v4l2_ctrl *ctrl)
{
	struct v4l2_ctrl **ctrls = v4l2_flash->ctrls;
	enum led_brightness brightness;

	if (has_flash_op(v4l2_flash, intensity_to_led_brightness))
		brightness = call_flash_op(v4l2_flash,
					intensity_to_led_brightness,
					ctrl->val);
	else
		brightness = __intensity_to_led_brightness(ctrl, ctrl->val);
	/*
	 * In case a LED Flash class driver provides ops for custom
	 * brightness <-> intensity conversion, it also must have defined
	 * related v4l2 control step == 1. In such a case a backward conversion
	 * from led brightness to v4l2 intensity is required to find out the
	 * the aligned intensity value.
	 */
	if (has_flash_op(v4l2_flash, led_brightness_to_intensity))
		ctrl->val = call_flash_op(v4l2_flash,
					led_brightness_to_intensity,
					brightness);

	if (ctrl == ctrls[TORCH_INTENSITY]) {
		if (ctrls[LED_MODE]->val != V4L2_FLASH_LED_MODE_TORCH)
			return;

		led_set_brightness_sync(&v4l2_flash->fled_cdev->led_cdev,
					brightness);
	} else {
		led_set_brightness_sync(v4l2_flash->iled_cdev,
					brightness);
	}
}