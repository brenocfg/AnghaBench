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
struct v4l2_flash {struct led_classdev_flash* fled_cdev; } ;
struct v4l2_ctrl {int id; int val; } ;
struct TYPE_2__ {int val; } ;
struct led_classdev_flash {TYPE_1__ brightness; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_FLASH_FAULT 132 
#define  V4L2_CID_FLASH_INDICATOR_INTENSITY 131 
#define  V4L2_CID_FLASH_INTENSITY 130 
#define  V4L2_CID_FLASH_STROBE_STATUS 129 
#define  V4L2_CID_FLASH_TORCH_INTENSITY 128 
 int led_get_flash_fault (struct led_classdev_flash*,int*) ; 
 int led_get_flash_strobe (struct led_classdev_flash*,int*) ; 
 int led_update_flash_brightness (struct led_classdev_flash*) ; 
 struct v4l2_flash* v4l2_ctrl_to_v4l2_flash (struct v4l2_ctrl*) ; 
 int v4l2_flash_update_led_brightness (struct v4l2_flash*,struct v4l2_ctrl*) ; 

__attribute__((used)) static int v4l2_flash_g_volatile_ctrl(struct v4l2_ctrl *c)
{
	struct v4l2_flash *v4l2_flash = v4l2_ctrl_to_v4l2_flash(c);
	struct led_classdev_flash *fled_cdev = v4l2_flash->fled_cdev;
	bool is_strobing;
	int ret;

	switch (c->id) {
	case V4L2_CID_FLASH_TORCH_INTENSITY:
	case V4L2_CID_FLASH_INDICATOR_INTENSITY:
		return v4l2_flash_update_led_brightness(v4l2_flash, c);
	case V4L2_CID_FLASH_INTENSITY:
		ret = led_update_flash_brightness(fled_cdev);
		if (ret < 0)
			return ret;
		/*
		 * No conversion is needed as LED Flash class also uses
		 * microamperes for flash intensity units.
		 */
		c->val = fled_cdev->brightness.val;
		return 0;
	case V4L2_CID_FLASH_STROBE_STATUS:
		ret = led_get_flash_strobe(fled_cdev, &is_strobing);
		if (ret < 0)
			return ret;
		c->val = is_strobing;
		return 0;
	case V4L2_CID_FLASH_FAULT:
		/* LED faults map directly to V4L2 flash faults */
		return led_get_flash_fault(fled_cdev, &c->val);
	default:
		return -EINVAL;
	}
}