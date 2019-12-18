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
typedef  scalar_t__ uint8_t ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kone_command_weight ; 
 int kone_receive (struct usb_device*,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static int kone_get_weight(struct usb_device *usb_dev, int *result)
{
	int retval;
	uint8_t data;

	retval = kone_receive(usb_dev, kone_command_weight, &data, 1);

	if (retval)
		return retval;

	*result = (int)data;
	return 0;
}