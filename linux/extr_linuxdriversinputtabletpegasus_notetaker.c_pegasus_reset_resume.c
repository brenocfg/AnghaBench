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
struct usb_interface {int dummy; } ;
struct pegasus {int /*<<< orphan*/  pm_mutex; int /*<<< orphan*/  irq; scalar_t__ is_open; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  NOTETAKER_LED_MOUSE ; 
 int /*<<< orphan*/  PEN_MODE_XY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pegasus_set_mode (struct pegasus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pegasus* usb_get_intfdata (struct usb_interface*) ; 
 scalar_t__ usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pegasus_reset_resume(struct usb_interface *intf)
{
	struct pegasus *pegasus = usb_get_intfdata(intf);
	int retval = 0;

	mutex_lock(&pegasus->pm_mutex);
	if (pegasus->is_open) {
		retval = pegasus_set_mode(pegasus, PEN_MODE_XY,
					  NOTETAKER_LED_MOUSE);
		if (!retval && usb_submit_urb(pegasus->irq, GFP_NOIO) < 0)
			retval = -EIO;
	}
	mutex_unlock(&pegasus->pm_mutex);

	return retval;
}