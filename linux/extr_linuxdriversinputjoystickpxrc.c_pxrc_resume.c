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
struct pxrc {int /*<<< orphan*/  pm_mutex; int /*<<< orphan*/  urb; scalar_t__ is_open; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct pxrc* usb_get_intfdata (struct usb_interface*) ; 
 scalar_t__ usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pxrc_resume(struct usb_interface *intf)
{
	struct pxrc *pxrc = usb_get_intfdata(intf);
	int retval = 0;

	mutex_lock(&pxrc->pm_mutex);
	if (pxrc->is_open && usb_submit_urb(pxrc->urb, GFP_KERNEL) < 0)
		retval = -EIO;

	mutex_unlock(&pxrc->pm_mutex);
	return retval;
}