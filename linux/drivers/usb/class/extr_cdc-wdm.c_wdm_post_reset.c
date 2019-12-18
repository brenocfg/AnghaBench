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
struct wdm_device {int /*<<< orphan*/  rlock; int /*<<< orphan*/  wlock; int /*<<< orphan*/  flags; } ;
struct usb_interface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WDM_OVERFLOW ; 
 int /*<<< orphan*/  WDM_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int recover_from_urb_loss (struct wdm_device*) ; 
 struct wdm_device* wdm_find_device (struct usb_interface*) ; 

__attribute__((used)) static int wdm_post_reset(struct usb_interface *intf)
{
	struct wdm_device *desc = wdm_find_device(intf);
	int rv;

	clear_bit(WDM_OVERFLOW, &desc->flags);
	clear_bit(WDM_RESETTING, &desc->flags);
	rv = recover_from_urb_loss(desc);
	mutex_unlock(&desc->wlock);
	mutex_unlock(&desc->rlock);
	return rv;
}