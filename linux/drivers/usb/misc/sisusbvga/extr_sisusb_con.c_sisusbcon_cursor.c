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
struct TYPE_2__ {int height; } ;
struct vc_data {scalar_t__ vc_origin; scalar_t__ vc_visible_origin; int vc_pos; int vc_cursor_type; TYPE_1__ vc_font; int /*<<< orphan*/  vc_num; } ;
struct sisusb_usb_data {int sisusb_cursor_size_to; int scrbuf; int sisusb_cursor_size_from; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int CM_ERASE ; 
#define  CUR_BLOCK 133 
#define  CUR_LOWER_HALF 132 
#define  CUR_LOWER_THIRD 131 
#define  CUR_NONE 130 
#define  CUR_TWO_THIRDS 129 
#define  CUR_UNDERLINE 128 
 int /*<<< orphan*/  SISCR ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sisusb_usb_data* sisusb_get_sisusb_lock_and_check (int /*<<< orphan*/ ) ; 
 scalar_t__ sisusb_is_inactive (struct vc_data*,struct sisusb_usb_data*) ; 
 int /*<<< orphan*/  sisusb_set_cursor (struct sisusb_usb_data*,int) ; 
 int /*<<< orphan*/  sisusb_setidxreg (struct sisusb_usb_data*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sisusb_setidxregandor (struct sisusb_usb_data*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sisusb_setidxregor (struct sisusb_usb_data*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sisusbcon_set_start_address (struct sisusb_usb_data*,struct vc_data*) ; 

__attribute__((used)) static void
sisusbcon_cursor(struct vc_data *c, int mode)
{
	struct sisusb_usb_data *sisusb;
	int from, to, baseline;

	sisusb = sisusb_get_sisusb_lock_and_check(c->vc_num);
	if (!sisusb)
		return;

	/* sisusb->lock is down */

	if (sisusb_is_inactive(c, sisusb)) {
		mutex_unlock(&sisusb->lock);
		return;
	}

	if (c->vc_origin != c->vc_visible_origin) {
		c->vc_visible_origin = c->vc_origin;
		sisusbcon_set_start_address(sisusb, c);
	}

	if (mode == CM_ERASE) {
		sisusb_setidxregor(sisusb, SISCR, 0x0a, 0x20);
		sisusb->sisusb_cursor_size_to = -1;
		mutex_unlock(&sisusb->lock);
		return;
	}

	sisusb_set_cursor(sisusb, (c->vc_pos - sisusb->scrbuf) / 2);

	baseline = c->vc_font.height - (c->vc_font.height < 10 ? 1 : 2);

	switch (c->vc_cursor_type & 0x0f) {
		case CUR_BLOCK:		from = 1;
					to   = c->vc_font.height;
					break;
		case CUR_TWO_THIRDS:	from = c->vc_font.height / 3;
					to   = baseline;
					break;
		case CUR_LOWER_HALF:	from = c->vc_font.height / 2;
					to   = baseline;
					break;
		case CUR_LOWER_THIRD:	from = (c->vc_font.height * 2) / 3;
					to   = baseline;
					break;
		case CUR_NONE:		from = 31;
					to = 30;
					break;
		default:
		case CUR_UNDERLINE:	from = baseline - 1;
					to   = baseline;
					break;
	}

	if (sisusb->sisusb_cursor_size_from != from ||
	    sisusb->sisusb_cursor_size_to != to) {

		sisusb_setidxreg(sisusb, SISCR, 0x0a, from);
		sisusb_setidxregandor(sisusb, SISCR, 0x0b, 0xe0, to);

		sisusb->sisusb_cursor_size_from = from;
		sisusb->sisusb_cursor_size_to   = to;
	}

	mutex_unlock(&sisusb->lock);
}