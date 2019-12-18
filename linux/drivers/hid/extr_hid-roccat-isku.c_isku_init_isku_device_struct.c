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
struct isku_device {int /*<<< orphan*/  isku_lock; } ;

/* Variables and functions */
 int isku_get_actual_profile (struct usb_device*) ; 
 int /*<<< orphan*/  isku_profile_activated (struct isku_device*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int isku_init_isku_device_struct(struct usb_device *usb_dev,
		struct isku_device *isku)
{
	int retval;

	mutex_init(&isku->isku_lock);

	retval = isku_get_actual_profile(usb_dev);
	if (retval < 0)
		return retval;
	isku_profile_activated(isku, retval);

	return 0;
}