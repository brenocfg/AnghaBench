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
struct kvaser_usb {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int kvaser_usb_leaf_get_software_info_inner (struct kvaser_usb*) ; 

__attribute__((used)) static int kvaser_usb_leaf_get_software_info(struct kvaser_usb *dev)
{
	int err;
	int retry = 3;

	/* On some x86 laptops, plugging a Kvaser device again after
	 * an unplug makes the firmware always ignore the very first
	 * command. For such a case, provide some room for retries
	 * instead of completely exiting the driver.
	 */
	do {
		err = kvaser_usb_leaf_get_software_info_inner(dev);
	} while (--retry && err == -ETIMEDOUT);

	return err;
}