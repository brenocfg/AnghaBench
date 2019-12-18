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
struct v4l2_flash {struct v4l2_ctrl** ctrls; struct led_classdev_flash* fled_cdev; } ;
struct v4l2_ctrl {int id; int const val; } ;
struct led_classdev {int dummy; } ;
struct led_classdev_flash {struct led_classdev led_cdev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 size_t LED_MODE ; 
 int /*<<< orphan*/  LED_OFF ; 
 size_t STROBE_SOURCE ; 
 size_t TORCH_INTENSITY ; 
#define  V4L2_CID_FLASH_INDICATOR_INTENSITY 138 
#define  V4L2_CID_FLASH_INTENSITY 137 
#define  V4L2_CID_FLASH_LED_MODE 136 
#define  V4L2_CID_FLASH_STROBE 135 
#define  V4L2_CID_FLASH_STROBE_SOURCE 134 
#define  V4L2_CID_FLASH_STROBE_STOP 133 
#define  V4L2_CID_FLASH_TIMEOUT 132 
#define  V4L2_CID_FLASH_TORCH_INTENSITY 131 
#define  V4L2_FLASH_LED_MODE_FLASH 130 
#define  V4L2_FLASH_LED_MODE_NONE 129 
#define  V4L2_FLASH_LED_MODE_TORCH 128 
 int const V4L2_FLASH_STROBE_SOURCE_EXTERNAL ; 
 int /*<<< orphan*/  __software_strobe_mode_inactive (struct v4l2_ctrl**) ; 
 int call_flash_op (struct v4l2_flash*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  external_strobe_set ; 
 int /*<<< orphan*/  led_set_brightness_sync (struct led_classdev*,int /*<<< orphan*/ ) ; 
 int led_set_flash_brightness (struct led_classdev_flash*,int const) ; 
 int led_set_flash_strobe (struct led_classdev_flash*,int) ; 
 int led_set_flash_timeout (struct led_classdev_flash*,int const) ; 
 struct v4l2_flash* v4l2_ctrl_to_v4l2_flash (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  v4l2_flash_set_led_brightness (struct v4l2_flash*,struct v4l2_ctrl*) ; 

__attribute__((used)) static int v4l2_flash_s_ctrl(struct v4l2_ctrl *c)
{
	struct v4l2_flash *v4l2_flash = v4l2_ctrl_to_v4l2_flash(c);
	struct led_classdev_flash *fled_cdev = v4l2_flash->fled_cdev;
	struct led_classdev *led_cdev = fled_cdev ? &fled_cdev->led_cdev : NULL;
	struct v4l2_ctrl **ctrls = v4l2_flash->ctrls;
	bool external_strobe;
	int ret = 0;

	switch (c->id) {
	case V4L2_CID_FLASH_LED_MODE:
		switch (c->val) {
		case V4L2_FLASH_LED_MODE_NONE:
			led_set_brightness_sync(led_cdev, LED_OFF);
			return led_set_flash_strobe(fled_cdev, false);
		case V4L2_FLASH_LED_MODE_FLASH:
			/* Turn the torch LED off */
			led_set_brightness_sync(led_cdev, LED_OFF);
			if (ctrls[STROBE_SOURCE]) {
				external_strobe = (ctrls[STROBE_SOURCE]->val ==
					V4L2_FLASH_STROBE_SOURCE_EXTERNAL);

				ret = call_flash_op(v4l2_flash,
						external_strobe_set,
						external_strobe);
			}
			return ret;
		case V4L2_FLASH_LED_MODE_TORCH:
			if (ctrls[STROBE_SOURCE]) {
				ret = call_flash_op(v4l2_flash,
						external_strobe_set,
						false);
				if (ret < 0)
					return ret;
			}
			/* Stop flash strobing */
			ret = led_set_flash_strobe(fled_cdev, false);
			if (ret < 0)
				return ret;

			v4l2_flash_set_led_brightness(v4l2_flash,
							ctrls[TORCH_INTENSITY]);
			return 0;
		}
		break;
	case V4L2_CID_FLASH_STROBE_SOURCE:
		external_strobe = (c->val == V4L2_FLASH_STROBE_SOURCE_EXTERNAL);
		/*
		 * For some hardware arrangements setting strobe source may
		 * affect torch mode. Therefore, if not in the flash mode,
		 * cache only this setting. It will be applied upon switching
		 * to flash mode.
		 */
		if (ctrls[LED_MODE]->val != V4L2_FLASH_LED_MODE_FLASH)
			return 0;

		return call_flash_op(v4l2_flash, external_strobe_set,
					external_strobe);
	case V4L2_CID_FLASH_STROBE:
		if (__software_strobe_mode_inactive(ctrls))
			return -EBUSY;
		return led_set_flash_strobe(fled_cdev, true);
	case V4L2_CID_FLASH_STROBE_STOP:
		if (__software_strobe_mode_inactive(ctrls))
			return -EBUSY;
		return led_set_flash_strobe(fled_cdev, false);
	case V4L2_CID_FLASH_TIMEOUT:
		/*
		 * No conversion is needed as LED Flash class also uses
		 * microseconds for flash timeout units.
		 */
		return led_set_flash_timeout(fled_cdev, c->val);
	case V4L2_CID_FLASH_INTENSITY:
		/*
		 * No conversion is needed as LED Flash class also uses
		 * microamperes for flash intensity units.
		 */
		return led_set_flash_brightness(fled_cdev, c->val);
	case V4L2_CID_FLASH_TORCH_INTENSITY:
	case V4L2_CID_FLASH_INDICATOR_INTENSITY:
		v4l2_flash_set_led_brightness(v4l2_flash, c);
		return 0;
	}

	return -EINVAL;
}