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
struct usb_usbvision {size_t scratch_headermarker_write_ptr; int /*<<< orphan*/  scratch_write_ptr; int /*<<< orphan*/ * scratch_headermarker; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_SCRATCH ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,size_t) ; 
 int USBVISION_NUM_HEADERMARKER ; 

__attribute__((used)) static void scratch_mark_header(struct usb_usbvision *usbvision)
{
	PDEBUG(DBG_SCRATCH, "header at write_ptr=%d\n", usbvision->scratch_headermarker_write_ptr);

	usbvision->scratch_headermarker[usbvision->scratch_headermarker_write_ptr] =
				usbvision->scratch_write_ptr;
	usbvision->scratch_headermarker_write_ptr += 1;
	usbvision->scratch_headermarker_write_ptr %= USBVISION_NUM_HEADERMARKER;
}