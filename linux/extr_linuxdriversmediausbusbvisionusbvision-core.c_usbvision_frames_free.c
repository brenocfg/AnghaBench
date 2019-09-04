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
struct usb_usbvision {scalar_t__ num_frames; int /*<<< orphan*/ * fbuf; int /*<<< orphan*/  fbuf_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  usbvision_rvfree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void usbvision_frames_free(struct usb_usbvision *usbvision)
{
	/* Have to free all that memory */
	PDEBUG(DBG_FUNC, "free %d frames", usbvision->num_frames);

	if (usbvision->fbuf != NULL) {
		usbvision_rvfree(usbvision->fbuf, usbvision->fbuf_size);
		usbvision->fbuf = NULL;

		usbvision->num_frames = 0;
	}
}