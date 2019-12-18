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
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kone_command_calibrate ; 
 int kone_send (struct usb_device*,int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int kone_tcu_command(struct usb_device *usb_dev, int number)
{
	unsigned char value;

	value = number;
	return kone_send(usb_dev, kone_command_calibrate, &value, 1);
}