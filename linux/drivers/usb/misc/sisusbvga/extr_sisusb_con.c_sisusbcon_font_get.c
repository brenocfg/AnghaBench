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
struct TYPE_2__ {int /*<<< orphan*/  height; } ;
struct vc_data {TYPE_1__ vc_font; int /*<<< orphan*/  vc_num; } ;
struct sisusb_usb_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  font_backup; } ;
struct console_font {int width; int charcount; int /*<<< orphan*/  data; int /*<<< orphan*/  height; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sisusb_usb_data* sisusb_get_sisusb_lock_and_check (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sisusbcon_font_get(struct vc_data *c, struct console_font *font)
{
	struct sisusb_usb_data *sisusb;

	sisusb = sisusb_get_sisusb_lock_and_check(c->vc_num);
	if (!sisusb)
		return -ENODEV;

	/* sisusb->lock is down */

	font->width = 8;
	font->height = c->vc_font.height;
	font->charcount = 256;

	if (!font->data) {
		mutex_unlock(&sisusb->lock);
		return 0;
	}

	if (!sisusb->font_backup) {
		mutex_unlock(&sisusb->lock);
		return -ENODEV;
	}

	/* Copy 256 chars only, like vgacon */
	memcpy(font->data, sisusb->font_backup, 256 * 32);

	mutex_unlock(&sisusb->lock);

	return 0;
}