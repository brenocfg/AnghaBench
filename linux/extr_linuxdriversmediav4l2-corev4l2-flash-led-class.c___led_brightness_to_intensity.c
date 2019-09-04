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
struct v4l2_ctrl {scalar_t__ id; int step; scalar_t__ minimum; } ;
typedef  scalar_t__ s32 ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 scalar_t__ V4L2_CID_FLASH_INDICATOR_INTENSITY ; 

__attribute__((used)) static s32 __led_brightness_to_intensity(struct v4l2_ctrl *ctrl,
					 enum led_brightness brightness)
{
	/*
	 * Indicator LEDs, unlike torch LEDs, are turned on/off basing on
	 * the state of V4L2_CID_FLASH_INDICATOR_INTENSITY control only.
	 * Do not decrement brightness read from the LED subsystem for
	 * indicator LED as it may equal 0. For torch LEDs this function
	 * is called only when V4L2_FLASH_LED_MODE_TORCH is set and the
	 * brightness read is guaranteed to be greater than 0. In the mode
	 * V4L2_FLASH_LED_MODE_NONE the cached torch intensity value is used.
	 */
	if (ctrl->id != V4L2_CID_FLASH_INDICATOR_INTENSITY)
		--brightness;

	return (brightness * ctrl->step) + ctrl->minimum;
}