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
typedef  enum usb_dr_mode { ____Placeholder_usb_dr_mode } usb_dr_mode ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int USB_DR_MODE_UNKNOWN ; 
 int match_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  usb_dr_modes ; 

__attribute__((used)) static enum usb_dr_mode usb_get_dr_mode_from_string(const char *str)
{
	int ret;

	ret = match_string(usb_dr_modes, ARRAY_SIZE(usb_dr_modes), str);
	return (ret < 0) ? USB_DR_MODE_UNKNOWN : ret;
}