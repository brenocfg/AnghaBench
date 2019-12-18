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
struct vc_data {int* vc_palette; int /*<<< orphan*/  vc_num; } ;
struct sisusb_usb_data {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SISCOLDATA ; 
 int /*<<< orphan*/  SISCOLIDX ; 
 int /*<<< orphan*/  con_is_visible (struct vc_data*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sisusb_usb_data* sisusb_get_sisusb_lock_and_check (int /*<<< orphan*/ ) ; 
 scalar_t__ sisusb_is_inactive (struct vc_data*,struct sisusb_usb_data*) ; 
 scalar_t__ sisusb_setreg (struct sisusb_usb_data*,int /*<<< orphan*/ ,unsigned char const) ; 

__attribute__((used)) static void
sisusbcon_set_palette(struct vc_data *c, const unsigned char *table)
{
	struct sisusb_usb_data *sisusb;
	int i, j;

	/* Return value not used by vt */

	if (!con_is_visible(c))
		return;

	sisusb = sisusb_get_sisusb_lock_and_check(c->vc_num);
	if (!sisusb)
		return;

	/* sisusb->lock is down */

	if (sisusb_is_inactive(c, sisusb)) {
		mutex_unlock(&sisusb->lock);
		return;
	}

	for (i = j = 0; i < 16; i++) {
		if (sisusb_setreg(sisusb, SISCOLIDX, table[i]))
			break;
		if (sisusb_setreg(sisusb, SISCOLDATA, c->vc_palette[j++] >> 2))
			break;
		if (sisusb_setreg(sisusb, SISCOLDATA, c->vc_palette[j++] >> 2))
			break;
		if (sisusb_setreg(sisusb, SISCOLDATA, c->vc_palette[j++] >> 2))
			break;
	}

	mutex_unlock(&sisusb->lock);
}