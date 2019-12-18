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
struct vc_data {int /*<<< orphan*/  vc_num; } ;
struct sisusb_usb_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  scrbuf_size; scalar_t__ scrbuf; int /*<<< orphan*/  con_rolled_over; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sisusb_usb_data* sisusb_get_sisusb_lock_and_check (int /*<<< orphan*/ ) ; 
 scalar_t__ sisusb_is_inactive (struct vc_data*,struct sisusb_usb_data*) ; 
 int /*<<< orphan*/  sisusbcon_set_start_address (struct sisusb_usb_data*,struct vc_data*) ; 
 int /*<<< orphan*/  vc_scrolldelta_helper (struct vc_data*,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sisusbcon_scrolldelta(struct vc_data *c, int lines)
{
	struct sisusb_usb_data *sisusb;

	sisusb = sisusb_get_sisusb_lock_and_check(c->vc_num);
	if (!sisusb)
		return;

	/* sisusb->lock is down */

	if (sisusb_is_inactive(c, sisusb)) {
		mutex_unlock(&sisusb->lock);
		return;
	}

	vc_scrolldelta_helper(c, lines, sisusb->con_rolled_over,
			(void *)sisusb->scrbuf, sisusb->scrbuf_size);

	sisusbcon_set_start_address(sisusb, c);

	mutex_unlock(&sisusb->lock);
}