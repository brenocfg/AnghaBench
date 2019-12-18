#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct vc_data {unsigned long vc_origin; scalar_t__ vc_screenbuf; scalar_t__ vc_screenbuf_size; int /*<<< orphan*/  vc_num; } ;
struct sisusb_usb_data {unsigned long scrbuf; unsigned long scrbuf_size; int /*<<< orphan*/  lock; TYPE_1__* sisusb_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sisusb_copy_memory (struct sisusb_usb_data*,char*,int /*<<< orphan*/ ,int) ; 
 struct sisusb_usb_data* sisusb_get_sisusb_lock_and_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sisusb_haddr (struct sisusb_usb_data*,struct vc_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sisusb_is_inactive (struct vc_data*,struct sisusb_usb_data*) ; 

__attribute__((used)) static int
sisusbcon_switch(struct vc_data *c)
{
	struct sisusb_usb_data *sisusb;
	int length;

	/* Returnvalue 0 means we have fully restored screen,
	 *	and vt doesn't need to call do_update_region().
	 * Returnvalue != 0 naturally means the opposite.
	 */

	sisusb = sisusb_get_sisusb_lock_and_check(c->vc_num);
	if (!sisusb)
		return 0;

	/* sisusb->lock is down */

	/* Don't write to screen if in gfx mode */
	if (sisusb_is_inactive(c, sisusb)) {
		mutex_unlock(&sisusb->lock);
		return 0;
	}

	/* That really should not happen. It would mean we are
	 * being called while the vc is using its private buffer
	 * as origin.
	 */
	if (c->vc_origin == (unsigned long)c->vc_screenbuf) {
		mutex_unlock(&sisusb->lock);
		dev_dbg(&sisusb->sisusb_dev->dev, "ASSERT ORIGIN != SCREENBUF!\n");
		return 0;
	}

	/* Check that we don't copy too much */
	length = min((int)c->vc_screenbuf_size,
			(int)(sisusb->scrbuf + sisusb->scrbuf_size - c->vc_origin));

	/* Restore the screen contents */
	memcpy((u16 *)c->vc_origin, (u16 *)c->vc_screenbuf, length);

	sisusb_copy_memory(sisusb, (char *)c->vc_origin,
			sisusb_haddr(sisusb, c, 0, 0), length);

	mutex_unlock(&sisusb->lock);

	return 0;
}