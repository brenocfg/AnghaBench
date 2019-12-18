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
struct arvo_device {int actual_profile; int /*<<< orphan*/  arvo_lock; } ;

/* Variables and functions */
 int arvo_get_actual_profile (struct usb_device*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int arvo_init_arvo_device_struct(struct usb_device *usb_dev,
		struct arvo_device *arvo)
{
	int retval;

	mutex_init(&arvo->arvo_lock);

	retval = arvo_get_actual_profile(usb_dev);
	if (retval < 0)
		return retval;
	arvo->actual_profile = retval;

	return 0;
}