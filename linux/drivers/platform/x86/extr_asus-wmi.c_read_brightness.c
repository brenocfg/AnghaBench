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
typedef  int u32 ;
struct backlight_device {int dummy; } ;
struct asus_wmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_WMI_DEVID_BRIGHTNESS ; 
 int ASUS_WMI_DSTS_BRIGHTNESS_MASK ; 
 int asus_wmi_get_devstate (struct asus_wmi*,int /*<<< orphan*/ ,int*) ; 
 struct asus_wmi* bl_get_data (struct backlight_device*) ; 

__attribute__((used)) static int read_brightness(struct backlight_device *bd)
{
	struct asus_wmi *asus = bl_get_data(bd);
	u32 retval;
	int err;

	err = asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_BRIGHTNESS, &retval);
	if (err < 0)
		return err;

	return retval & ASUS_WMI_DSTS_BRIGHTNESS_MASK;
}