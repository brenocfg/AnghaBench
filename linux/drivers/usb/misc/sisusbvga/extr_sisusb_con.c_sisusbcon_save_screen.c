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
typedef  int /*<<< orphan*/  u16 ;
struct vc_data {scalar_t__ vc_origin; scalar_t__ vc_screenbuf; scalar_t__ vc_screenbuf_size; int /*<<< orphan*/  vc_num; } ;
struct sisusb_usb_data {int /*<<< orphan*/  lock; scalar_t__ scrbuf_size; scalar_t__ scrbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sisusb_usb_data* sisusb_get_sisusb_lock_and_check (int /*<<< orphan*/ ) ; 
 scalar_t__ sisusb_is_inactive (struct vc_data*,struct sisusb_usb_data*) ; 

__attribute__((used)) static void
sisusbcon_save_screen(struct vc_data *c)
{
	struct sisusb_usb_data *sisusb;
	int length;

	/* Save the current screen contents to vc's private
	 * buffer.
	 */

	sisusb = sisusb_get_sisusb_lock_and_check(c->vc_num);
	if (!sisusb)
		return;

	/* sisusb->lock is down */

	if (sisusb_is_inactive(c, sisusb)) {
		mutex_unlock(&sisusb->lock);
		return;
	}

	/* Check that we don't copy too much */
	length = min((int)c->vc_screenbuf_size,
			(int)(sisusb->scrbuf + sisusb->scrbuf_size - c->vc_origin));

	/* Save the screen contents to vc's private buffer */
	memcpy((u16 *)c->vc_screenbuf, (u16 *)c->vc_origin, length);

	mutex_unlock(&sisusb->lock);
}