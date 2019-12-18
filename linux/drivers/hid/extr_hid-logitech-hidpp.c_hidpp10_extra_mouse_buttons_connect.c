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
struct hidpp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIDPP_ENABLE_MOUSE_EXTRA_BTN_REPORT ; 
 int /*<<< orphan*/  HIDPP_REG_ENABLE_REPORTS ; 
 int hidpp10_set_register (struct hidpp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hidpp10_extra_mouse_buttons_connect(struct hidpp_device *hidpp)
{
	return hidpp10_set_register(hidpp, HIDPP_REG_ENABLE_REPORTS, 0,
				    HIDPP_ENABLE_MOUSE_EXTRA_BTN_REPORT,
				    HIDPP_ENABLE_MOUSE_EXTRA_BTN_REPORT);
}