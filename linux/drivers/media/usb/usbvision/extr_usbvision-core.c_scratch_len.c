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
struct usb_usbvision {int scratch_write_ptr; int scratch_read_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_SCRATCH ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ scratch_buf_size ; 

__attribute__((used)) static int scratch_len(struct usb_usbvision *usbvision)    /* This returns the amount of data actually in the buffer */
{
	int len = usbvision->scratch_write_ptr - usbvision->scratch_read_ptr;

	if (len < 0)
		len += scratch_buf_size;
	PDEBUG(DBG_SCRATCH, "scratch_len() = %d\n", len);

	return len;
}