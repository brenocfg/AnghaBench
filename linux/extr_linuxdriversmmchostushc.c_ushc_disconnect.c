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
struct ushc_data {int /*<<< orphan*/  mmc; int /*<<< orphan*/  csw_urb; int /*<<< orphan*/  data_urb; int /*<<< orphan*/  cbw_urb; int /*<<< orphan*/  int_urb; int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;
struct usb_interface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISCONNECTED ; 
 int /*<<< orphan*/  mmc_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct ushc_data* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ushc_clean_up (struct ushc_data*) ; 

__attribute__((used)) static void ushc_disconnect(struct usb_interface *intf)
{
	struct ushc_data *ushc = usb_get_intfdata(intf);

	spin_lock_irq(&ushc->lock);
	set_bit(DISCONNECTED, &ushc->flags);
	spin_unlock_irq(&ushc->lock);

	usb_kill_urb(ushc->int_urb);
	usb_kill_urb(ushc->cbw_urb);
	usb_kill_urb(ushc->data_urb);
	usb_kill_urb(ushc->csw_urb);

	mmc_remove_host(ushc->mmc);

	ushc_clean_up(ushc);
}