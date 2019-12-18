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
struct vc_data {int vc_cols; int /*<<< orphan*/  vc_num; int /*<<< orphan*/  vc_video_erase_char; } ;
struct sisusb_usb_data {int sisusb_num_columns; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sisusb_copy_memory (struct sisusb_usb_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct sisusb_usb_data* sisusb_get_sisusb_lock_and_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sisusb_haddr (struct sisusb_usb_data*,struct vc_data*,int,int) ; 
 scalar_t__ sisusb_is_inactive (struct vc_data*,struct sisusb_usb_data*) ; 
 int /*<<< orphan*/ * sisusb_vaddr (struct sisusb_usb_data*,struct vc_data*,int,int) ; 
 int /*<<< orphan*/  sisusbcon_memsetw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
sisusbcon_clear(struct vc_data *c, int y, int x, int height, int width)
{
	struct sisusb_usb_data *sisusb;
	u16 eattr = c->vc_video_erase_char;
	int i, length, cols;
	u16 *dest;

	if (width <= 0 || height <= 0)
		return;

	sisusb = sisusb_get_sisusb_lock_and_check(c->vc_num);
	if (!sisusb)
		return;

	/* sisusb->lock is down */

	/* Need to clear buffer ourselves, because the vt does
	 * this AFTER calling us.
	 */

	dest = sisusb_vaddr(sisusb, c, x, y);

	cols = sisusb->sisusb_num_columns;

	if (width > cols)
		width = cols;

	if (x == 0 && width >= c->vc_cols) {

		sisusbcon_memsetw(dest, eattr, height * cols * 2);

	} else {

		for (i = height; i > 0; i--, dest += cols)
			sisusbcon_memsetw(dest, eattr, width * 2);

	}

	if (sisusb_is_inactive(c, sisusb)) {
		mutex_unlock(&sisusb->lock);
		return;
	}

	length = ((height * cols) - x - (cols - width - x)) * 2;


	sisusb_copy_memory(sisusb, sisusb_vaddr(sisusb, c, x, y),
			sisusb_haddr(sisusb, c, x, y), length);

	mutex_unlock(&sisusb->lock);
}