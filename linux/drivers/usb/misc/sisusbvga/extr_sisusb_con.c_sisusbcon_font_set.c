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
struct sisusb_usb_data {unsigned int font_backup_size; int font_backup_512; int /*<<< orphan*/  font_backup_height; int /*<<< orphan*/ * font_backup; } ;
struct console_font {unsigned int charcount; int width; int /*<<< orphan*/  height; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 unsigned int KD_FONT_FLAG_DONT_RECALC ; 
 int /*<<< orphan*/  array_size (unsigned int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 struct sisusb_usb_data* sisusb_get_sisusb_lock_and_check (int /*<<< orphan*/ ) ; 
 int sisusbcon_do_font_op (struct sisusb_usb_data*,int,int,int /*<<< orphan*/ ,int,int,int,struct vc_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sisusbcon_font_set(struct vc_data *c, struct console_font *font,
		   unsigned int flags)
{
	struct sisusb_usb_data *sisusb;
	unsigned charcount = font->charcount;

	if (font->width != 8 || (charcount != 256 && charcount != 512))
		return -EINVAL;

	sisusb = sisusb_get_sisusb_lock_and_check(c->vc_num);
	if (!sisusb)
		return -ENODEV;

	/* sisusb->lock is down */

	/* Save the user-provided font into a buffer. This
	 * is used for restoring text mode after quitting
	 * from X and for the con_getfont routine.
	 */
	if (sisusb->font_backup) {
		if (sisusb->font_backup_size < charcount) {
			vfree(sisusb->font_backup);
			sisusb->font_backup = NULL;
		}
	}

	if (!sisusb->font_backup)
		sisusb->font_backup = vmalloc(array_size(charcount, 32));

	if (sisusb->font_backup) {
		memcpy(sisusb->font_backup, font->data, charcount * 32);
		sisusb->font_backup_size = charcount;
		sisusb->font_backup_height = font->height;
		sisusb->font_backup_512 = (charcount == 512) ? 1 : 0;
	}

	/* do_font_op ups sisusb->lock */

	return sisusbcon_do_font_op(sisusb, 1, 2, font->data,
			8192, (charcount == 512),
			(!(flags & KD_FONT_FLAG_DONT_RECALC)) ? 1 : 0,
			c, font->height, 1);
}