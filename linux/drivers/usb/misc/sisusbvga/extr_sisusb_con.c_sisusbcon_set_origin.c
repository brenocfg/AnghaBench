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
struct vc_data {int /*<<< orphan*/  vc_visible_origin; int /*<<< orphan*/  vc_origin; int /*<<< orphan*/  vc_num; } ;
struct sisusb_usb_data {int /*<<< orphan*/  lock; scalar_t__ con_rolled_over; int /*<<< orphan*/  scrbuf; scalar_t__ con_blanked; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sisusb_usb_data* sisusb_get_sisusb_lock_and_check (int /*<<< orphan*/ ) ; 
 scalar_t__ sisusb_is_inactive (struct vc_data*,struct sisusb_usb_data*) ; 
 int /*<<< orphan*/  sisusbcon_set_start_address (struct sisusb_usb_data*,struct vc_data*) ; 

__attribute__((used)) static int
sisusbcon_set_origin(struct vc_data *c)
{
	struct sisusb_usb_data *sisusb;

	/* Returning != 0 means we were successful.
	 * Returning 0 will vt make to use its own
	 *	screenbuffer as the origin.
	 */

	sisusb = sisusb_get_sisusb_lock_and_check(c->vc_num);
	if (!sisusb)
		return 0;

	/* sisusb->lock is down */

	if (sisusb_is_inactive(c, sisusb) || sisusb->con_blanked) {
		mutex_unlock(&sisusb->lock);
		return 0;
	}

	c->vc_origin = c->vc_visible_origin = sisusb->scrbuf;

	sisusbcon_set_start_address(sisusb, c);

	sisusb->con_rolled_over = 0;

	mutex_unlock(&sisusb->lock);

	return true;
}