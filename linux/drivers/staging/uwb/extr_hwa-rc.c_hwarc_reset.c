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
struct uwb_rc {struct hwarc* priv; } ;
struct hwarc {int /*<<< orphan*/  usb_dev; } ;

/* Variables and functions */
 int usb_lock_device_for_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int usb_reset_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unlock_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int hwarc_reset(struct uwb_rc *uwb_rc)
{
	struct hwarc *hwarc = uwb_rc->priv;
	int result;

	/* device lock must be held when calling usb_reset_device. */
	result = usb_lock_device_for_reset(hwarc->usb_dev, NULL);
	if (result >= 0) {
		result = usb_reset_device(hwarc->usb_dev);
		usb_unlock_device(hwarc->usb_dev);
	}

	return result;
}