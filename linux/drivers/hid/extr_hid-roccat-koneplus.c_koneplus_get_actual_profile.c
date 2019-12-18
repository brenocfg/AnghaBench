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
struct koneplus_actual_profile {int actual_profile; } ;

/* Variables and functions */
 int /*<<< orphan*/  KONEPLUS_COMMAND_ACTUAL_PROFILE ; 
 int /*<<< orphan*/  KONEPLUS_SIZE_ACTUAL_PROFILE ; 
 int roccat_common2_receive (struct usb_device*,int /*<<< orphan*/ ,struct koneplus_actual_profile*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int koneplus_get_actual_profile(struct usb_device *usb_dev)
{
	struct koneplus_actual_profile buf;
	int retval;

	retval = roccat_common2_receive(usb_dev, KONEPLUS_COMMAND_ACTUAL_PROFILE,
			&buf, KONEPLUS_SIZE_ACTUAL_PROFILE);

	return retval ? retval : buf.actual_profile;
}