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
struct v4l2_ctrl {scalar_t__ val; } ;

/* Variables and functions */
 size_t LED_MODE ; 
 size_t STROBE_SOURCE ; 
 scalar_t__ V4L2_FLASH_LED_MODE_FLASH ; 
 scalar_t__ V4L2_FLASH_STROBE_SOURCE_SOFTWARE ; 

__attribute__((used)) static bool __software_strobe_mode_inactive(struct v4l2_ctrl **ctrls)
{
	return ((ctrls[LED_MODE]->val != V4L2_FLASH_LED_MODE_FLASH) ||
		(ctrls[STROBE_SOURCE] && (ctrls[STROBE_SOURCE]->val !=
				V4L2_FLASH_STROBE_SOURCE_SOFTWARE)));
}