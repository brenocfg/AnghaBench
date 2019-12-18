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
struct peak_usb_device {int /*<<< orphan*/  next_siblings; int /*<<< orphan*/  prev_siblings; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcan_usb_pro_dev_if (struct peak_usb_device*) ; 

__attribute__((used)) static void pcan_usb_pro_free(struct peak_usb_device *dev)
{
	/* last device: can free pcan_usb_pro_interface object now */
	if (!dev->prev_siblings && !dev->next_siblings)
		kfree(pcan_usb_pro_dev_if(dev));
}