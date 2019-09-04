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
typedef  int uint ;
struct usb_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  startup_profile; } ;
struct kone_device {TYPE_1__ settings; int /*<<< orphan*/  firmware_version; int /*<<< orphan*/ * profiles; int /*<<< orphan*/  kone_lock; } ;

/* Variables and functions */
 int kone_get_firmware_version (struct usb_device*,int /*<<< orphan*/ *) ; 
 int kone_get_profile (struct usb_device*,int /*<<< orphan*/ *,int) ; 
 int kone_get_settings (struct usb_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  kone_profile_activated (struct kone_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kone_init_kone_device_struct(struct usb_device *usb_dev,
		struct kone_device *kone)
{
	uint i;
	int retval;

	mutex_init(&kone->kone_lock);

	for (i = 0; i < 5; ++i) {
		retval = kone_get_profile(usb_dev, &kone->profiles[i], i + 1);
		if (retval)
			return retval;
	}

	retval = kone_get_settings(usb_dev, &kone->settings);
	if (retval)
		return retval;

	retval = kone_get_firmware_version(usb_dev, &kone->firmware_version);
	if (retval)
		return retval;

	kone_profile_activated(kone, kone->settings.startup_profile);

	return 0;
}