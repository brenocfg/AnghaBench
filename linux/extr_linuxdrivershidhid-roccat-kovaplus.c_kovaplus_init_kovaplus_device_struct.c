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
typedef  int uint ;
struct usb_device {int dummy; } ;
struct kovaplus_device {int /*<<< orphan*/ * profile_buttons; int /*<<< orphan*/ * profile_settings; int /*<<< orphan*/  kovaplus_lock; } ;

/* Variables and functions */
 int kovaplus_get_actual_profile (struct usb_device*) ; 
 int kovaplus_get_profile_buttons (struct usb_device*,int /*<<< orphan*/ *,int) ; 
 int kovaplus_get_profile_settings (struct usb_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kovaplus_profile_activated (struct kovaplus_device*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kovaplus_init_kovaplus_device_struct(struct usb_device *usb_dev,
		struct kovaplus_device *kovaplus)
{
	int retval, i;
	static uint wait = 70; /* device will freeze with just 60 */

	mutex_init(&kovaplus->kovaplus_lock);

	for (i = 0; i < 5; ++i) {
		msleep(wait);
		retval = kovaplus_get_profile_settings(usb_dev,
				&kovaplus->profile_settings[i], i);
		if (retval)
			return retval;

		msleep(wait);
		retval = kovaplus_get_profile_buttons(usb_dev,
				&kovaplus->profile_buttons[i], i);
		if (retval)
			return retval;
	}

	msleep(wait);
	retval = kovaplus_get_actual_profile(usb_dev);
	if (retval < 0)
		return retval;
	kovaplus_profile_activated(kovaplus, retval);

	return 0;
}