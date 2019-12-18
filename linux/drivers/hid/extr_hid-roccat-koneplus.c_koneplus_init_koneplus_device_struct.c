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
struct usb_device {int dummy; } ;
struct koneplus_device {int /*<<< orphan*/  koneplus_lock; } ;

/* Variables and functions */
 int koneplus_get_actual_profile (struct usb_device*) ; 
 int /*<<< orphan*/  koneplus_profile_activated (struct koneplus_device*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int koneplus_init_koneplus_device_struct(struct usb_device *usb_dev,
		struct koneplus_device *koneplus)
{
	int retval;

	mutex_init(&koneplus->koneplus_lock);

	retval = koneplus_get_actual_profile(usb_dev);
	if (retval < 0)
		return retval;
	koneplus_profile_activated(koneplus, retval);

	return 0;
}