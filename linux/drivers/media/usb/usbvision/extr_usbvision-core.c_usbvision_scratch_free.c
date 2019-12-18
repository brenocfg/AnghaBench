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
struct usb_usbvision {int /*<<< orphan*/ * scratch; } ;

/* Variables and functions */
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

void usbvision_scratch_free(struct usb_usbvision *usbvision)
{
	vfree(usbvision->scratch);
	usbvision->scratch = NULL;
}