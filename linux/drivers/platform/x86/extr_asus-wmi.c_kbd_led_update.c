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
struct asus_wmi {int kbd_led_wk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_WMI_DEVID_KBD_BACKLIGHT ; 
 int /*<<< orphan*/  asus_wmi_set_devstate (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kbd_led_update(struct asus_wmi *asus)
{
	int ctrl_param = 0;

	/*
	 * bits 0-2: level
	 * bit 7: light on/off
	 */
	if (asus->kbd_led_wk > 0)
		ctrl_param = 0x80 | (asus->kbd_led_wk & 0x7F);

	asus_wmi_set_devstate(ASUS_WMI_DEVID_KBD_BACKLIGHT, ctrl_param, NULL);
}