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
typedef  size_t u32 ;
struct usb_usbvision {TYPE_1__* frame; int /*<<< orphan*/  outqueue; int /*<<< orphan*/  inqueue; } ;
struct TYPE_2__ {scalar_t__ bytes_read; int /*<<< orphan*/  grabstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 size_t USBVISION_NUMFRAMES ; 
 int /*<<< orphan*/  frame_state_unused ; 

void usbvision_empty_framequeues(struct usb_usbvision *usbvision)
{
	u32 i;

	INIT_LIST_HEAD(&(usbvision->inqueue));
	INIT_LIST_HEAD(&(usbvision->outqueue));

	for (i = 0; i < USBVISION_NUMFRAMES; i++) {
		usbvision->frame[i].grabstate = frame_state_unused;
		usbvision->frame[i].bytes_read = 0;
	}
}