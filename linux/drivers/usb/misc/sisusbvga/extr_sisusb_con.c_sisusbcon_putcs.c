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
struct sisusb_usb_data {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned short const*,int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sisusb_copy_memory (struct sisusb_usb_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct sisusb_usb_data* sisusb_get_sisusb_lock_and_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sisusb_haddr (struct sisusb_usb_data*,struct vc_data*,int,int) ; 
 scalar_t__ sisusb_is_inactive (struct vc_data*,struct sisusb_usb_data*) ; 
 int /*<<< orphan*/  sisusb_vaddr (struct sisusb_usb_data*,struct vc_data*,int,int) ; 

__attribute__((used)) static void
sisusbcon_putcs(struct vc_data *c, const unsigned short *s,
		         int count, int y, int x)
{
	struct sisusb_usb_data *sisusb;

	sisusb = sisusb_get_sisusb_lock_and_check(c->vc_num);
	if (!sisusb)
		return;

	/* sisusb->lock is down */

	/* Need to put the characters into the buffer ourselves,
	 * because the vt does this AFTER calling us.
	 */

	memcpy(sisusb_vaddr(sisusb, c, x, y), s, count * 2);

	if (sisusb_is_inactive(c, sisusb)) {
		mutex_unlock(&sisusb->lock);
		return;
	}

	sisusb_copy_memory(sisusb, sisusb_vaddr(sisusb, c, x, y),
			sisusb_haddr(sisusb, c, x, y), count * 2);

	mutex_unlock(&sisusb->lock);
}