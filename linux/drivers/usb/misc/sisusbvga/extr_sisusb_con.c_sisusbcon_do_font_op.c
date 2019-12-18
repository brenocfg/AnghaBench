#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_4__ {int height; } ;
struct vc_data {int vc_hi_font_mask; int vc_scan_lines; TYPE_1__ vc_font; TYPE_3__* vc_sw; } ;
struct sisusb_usb_data {int font_slot; int current_font_512; int current_font_height; int sisusb_cursor_size_from; int sisusb_cursor_size_to; int /*<<< orphan*/  lock; scalar_t__ vrambase; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* con_cursor ) (struct vc_data*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {struct vc_data* d; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_DRAW ; 
 int EINVAL ; 
 int EIO ; 
 int MAX_NR_CONSOLES ; 
 int /*<<< orphan*/  SISAR ; 
 int /*<<< orphan*/  SISCR ; 
 int /*<<< orphan*/  SISGR ; 
 int /*<<< orphan*/  SISINPSTAT ; 
 int /*<<< orphan*/  SISSR ; 
 scalar_t__ con_is_visible (struct vc_data*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__ sisusb_con ; 
 int /*<<< orphan*/  sisusb_getidxreg (struct sisusb_usb_data*,int /*<<< orphan*/ ,int,unsigned char*) ; 
 int /*<<< orphan*/  sisusb_getreg (struct sisusb_usb_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sisusb_readb (struct sisusb_usb_data*,scalar_t__,int /*<<< orphan*/ *) ; 
 int sisusb_setidxreg (struct sisusb_usb_data*,int /*<<< orphan*/ ,int,unsigned char) ; 
 int /*<<< orphan*/  sisusb_setreg (struct sisusb_usb_data*,int /*<<< orphan*/ ,int) ; 
 int sisusb_writeb (struct sisusb_usb_data*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct vc_data*,int /*<<< orphan*/ ) ; 
 TYPE_2__* vc_cons ; 
 int /*<<< orphan*/  vc_resize (struct vc_data*,int /*<<< orphan*/ ,int) ; 

int
sisusbcon_do_font_op(struct sisusb_usb_data *sisusb, int set, int slot,
			u8 *arg, int cmapsz, int ch512, int dorecalc,
			struct vc_data *c, int fh, int uplock)
{
	int font_select = 0x00, i, err = 0;
	u32 offset = 0;
	u8 dummy;

	/* sisusb->lock is down */

	/*
	 * The default font is kept in slot 0.
	 * A user font is loaded in slot 2 (256 ch)
	 * or 2+3 (512 ch).
	 */

	if ((slot != 0 && slot != 2) || !fh) {
		if (uplock)
			mutex_unlock(&sisusb->lock);
		return -EINVAL;
	}

	if (set)
		sisusb->font_slot = slot;

	/* Default font is always 256 */
	if (slot == 0)
		ch512 = 0;
	else
		offset = 4 * cmapsz;

	font_select = (slot == 0) ? 0x00 : (ch512 ? 0x0e : 0x0a);

	err |= sisusb_setidxreg(sisusb, SISSR, 0x00, 0x01); /* Reset */
	err |= sisusb_setidxreg(sisusb, SISSR, 0x02, 0x04); /* Write to plane 2 */
	err |= sisusb_setidxreg(sisusb, SISSR, 0x04, 0x07); /* Memory mode a0-bf */
	err |= sisusb_setidxreg(sisusb, SISSR, 0x00, 0x03); /* Reset */

	if (err)
		goto font_op_error;

	err |= sisusb_setidxreg(sisusb, SISGR, 0x04, 0x03); /* Select plane read 2 */
	err |= sisusb_setidxreg(sisusb, SISGR, 0x05, 0x00); /* Disable odd/even */
	err |= sisusb_setidxreg(sisusb, SISGR, 0x06, 0x00); /* Address range a0-bf */

	if (err)
		goto font_op_error;

	if (arg) {
		if (set)
			for (i = 0; i < cmapsz; i++) {
				err |= sisusb_writeb(sisusb,
					sisusb->vrambase + offset + i,
					arg[i]);
				if (err)
					break;
			}
		else
			for (i = 0; i < cmapsz; i++) {
				err |= sisusb_readb(sisusb,
					sisusb->vrambase + offset + i,
					&arg[i]);
				if (err)
					break;
			}

		/*
		 * In 512-character mode, the character map is not contiguous if
		 * we want to remain EGA compatible -- which we do
		 */

		if (ch512) {
			if (set)
				for (i = 0; i < cmapsz; i++) {
					err |= sisusb_writeb(sisusb,
						sisusb->vrambase + offset +
							(2 * cmapsz) + i,
						arg[cmapsz + i]);
					if (err)
						break;
				}
			else
				for (i = 0; i < cmapsz; i++) {
					err |= sisusb_readb(sisusb,
						sisusb->vrambase + offset +
							(2 * cmapsz) + i,
						&arg[cmapsz + i]);
					if (err)
						break;
				}
		}
	}

	if (err)
		goto font_op_error;

	err |= sisusb_setidxreg(sisusb, SISSR, 0x00, 0x01); /* Reset */
	err |= sisusb_setidxreg(sisusb, SISSR, 0x02, 0x03); /* Write to planes 0+1 */
	err |= sisusb_setidxreg(sisusb, SISSR, 0x04, 0x03); /* Memory mode a0-bf */
	if (set)
		sisusb_setidxreg(sisusb, SISSR, 0x03, font_select);
	err |= sisusb_setidxreg(sisusb, SISSR, 0x00, 0x03); /* Reset end */

	if (err)
		goto font_op_error;

	err |= sisusb_setidxreg(sisusb, SISGR, 0x04, 0x00); /* Select plane read 0 */
	err |= sisusb_setidxreg(sisusb, SISGR, 0x05, 0x10); /* Enable odd/even */
	err |= sisusb_setidxreg(sisusb, SISGR, 0x06, 0x06); /* Address range b8-bf */

	if (err)
		goto font_op_error;

	if ((set) && (ch512 != sisusb->current_font_512)) {

		/* Font is shared among all our consoles.
		 * And so is the hi_font_mask.
		 */
		for (i = 0; i < MAX_NR_CONSOLES; i++) {
			struct vc_data *d = vc_cons[i].d;
			if (d && d->vc_sw == &sisusb_con)
				d->vc_hi_font_mask = ch512 ? 0x0800 : 0;
		}

		sisusb->current_font_512 = ch512;

		/* color plane enable register:
			256-char: enable intensity bit
			512-char: disable intensity bit */
		sisusb_getreg(sisusb, SISINPSTAT, &dummy);
		sisusb_setreg(sisusb, SISAR, 0x12);
		sisusb_setreg(sisusb, SISAR, ch512 ? 0x07 : 0x0f);

		sisusb_getreg(sisusb, SISINPSTAT, &dummy);
		sisusb_setreg(sisusb, SISAR, 0x20);
		sisusb_getreg(sisusb, SISINPSTAT, &dummy);
	}

	if (dorecalc) {

		/*
		 * Adjust the screen to fit a font of a certain height
		 */

		unsigned char ovr, vde, fsr;
		int rows = 0, maxscan = 0;

		if (c) {

			/* Number of video rows */
			rows = c->vc_scan_lines / fh;
			/* Scan lines to actually display-1 */
			maxscan = rows * fh - 1;

			/*printk(KERN_DEBUG "sisusb recalc rows %d maxscan %d fh %d sl %d\n",
				rows, maxscan, fh, c->vc_scan_lines);*/

			sisusb_getidxreg(sisusb, SISCR, 0x07, &ovr);
			vde = maxscan & 0xff;
			ovr = (ovr & 0xbd) |
			      ((maxscan & 0x100) >> 7) |
			      ((maxscan & 0x200) >> 3);
			sisusb_setidxreg(sisusb, SISCR, 0x07, ovr);
			sisusb_setidxreg(sisusb, SISCR, 0x12, vde);

		}

		sisusb_getidxreg(sisusb, SISCR, 0x09, &fsr);
		fsr = (fsr & 0xe0) | (fh - 1);
		sisusb_setidxreg(sisusb, SISCR, 0x09, fsr);
		sisusb->current_font_height = fh;

		sisusb->sisusb_cursor_size_from = -1;
		sisusb->sisusb_cursor_size_to   = -1;

	}

	if (uplock)
		mutex_unlock(&sisusb->lock);

	if (dorecalc && c) {
		int rows = c->vc_scan_lines / fh;

		/* Now adjust our consoles' size */

		for (i = 0; i < MAX_NR_CONSOLES; i++) {
			struct vc_data *vc = vc_cons[i].d;

			if (vc && vc->vc_sw == &sisusb_con) {
				if (con_is_visible(vc)) {
					vc->vc_sw->con_cursor(vc, CM_DRAW);
				}
				vc->vc_font.height = fh;
				vc_resize(vc, 0, rows);
			}
		}
	}

	return 0;

font_op_error:
	if (uplock)
		mutex_unlock(&sisusb->lock);

	return -EIO;
}