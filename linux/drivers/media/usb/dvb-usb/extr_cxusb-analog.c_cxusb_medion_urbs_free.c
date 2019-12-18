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
struct cxusb_medion_dev {TYPE_1__** streamurbs; } ;
struct TYPE_2__ {int /*<<< orphan*/  transfer_buffer; } ;

/* Variables and functions */
 unsigned int CXUSB_VIDEO_URBS ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_1__*) ; 

__attribute__((used)) static void cxusb_medion_urbs_free(struct cxusb_medion_dev *cxdev)
{
	unsigned int i;

	for (i = 0; i < CXUSB_VIDEO_URBS; i++)
		if (cxdev->streamurbs[i]) {
			kfree(cxdev->streamurbs[i]->transfer_buffer);
			usb_free_urb(cxdev->streamurbs[i]);
			cxdev->streamurbs[i] = NULL;
		}
}