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
struct asus_wmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_WMI_DEVID_KBD_BACKLIGHT ; 
 int asus_wmi_get_devstate_bits (struct asus_wmi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int kbd_led_read(struct asus_wmi *asus, int *level, int *env)
{
	int retval;

	/*
	 * bits 0-2: level
	 * bit 7: light on/off
	 * bit 8-10: environment (0: dark, 1: normal, 2: light)
	 * bit 17: status unknown
	 */
	retval = asus_wmi_get_devstate_bits(asus, ASUS_WMI_DEVID_KBD_BACKLIGHT,
					    0xFFFF);

	/* Unknown status is considered as off */
	if (retval == 0x8000)
		retval = 0;

	if (retval < 0)
		return retval;

	if (level)
		*level = retval & 0x7F;
	if (env)
		*env = (retval >> 8) & 0x7F;
	return 0;
}