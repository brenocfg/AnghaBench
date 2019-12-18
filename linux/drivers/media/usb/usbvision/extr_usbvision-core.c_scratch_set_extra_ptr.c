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
struct usb_usbvision {int scratch_read_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_SCRATCH ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int) ; 
 int scratch_buf_size ; 

__attribute__((used)) static void scratch_set_extra_ptr(struct usb_usbvision *usbvision, int *ptr,
				  int len)
{
	*ptr = (usbvision->scratch_read_ptr + len) % scratch_buf_size;

	PDEBUG(DBG_SCRATCH, "ptr=%d\n", *ptr);
}