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
struct vc_data {int vc_scan_lines; int /*<<< orphan*/  vc_num; } ;
struct sisusb_usb_data {int current_font_height; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sisusb_usb_data* sisusb_get_sisusb_lock_and_check (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sisusbcon_resize(struct vc_data *c, unsigned int newcols, unsigned int newrows,
		 unsigned int user)
{
	struct sisusb_usb_data *sisusb;
	int fh;

	sisusb = sisusb_get_sisusb_lock_and_check(c->vc_num);
	if (!sisusb)
		return -ENODEV;

	fh = sisusb->current_font_height;

	mutex_unlock(&sisusb->lock);

	/* We are quite unflexible as regards resizing. The vt code
	 * handles sizes where the line length isn't equal the pitch
	 * quite badly. As regards the rows, our panning tricks only
	 * work well if the number of rows equals the visible number
	 * of rows.
	 */

	if (newcols != 80 || c->vc_scan_lines / fh != newrows)
		return -EINVAL;

	return 0;
}