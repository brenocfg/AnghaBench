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
struct usb_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpucs_reg; } ;

/* Variables and functions */
 TYPE_1__ ezusb_fx1 ; 
 int ezusb_set_reset (struct usb_device*,int /*<<< orphan*/ ,unsigned char) ; 

int ezusb_fx1_set_reset(struct usb_device *dev, unsigned char reset_bit)
{
	return ezusb_set_reset(dev, ezusb_fx1.cpucs_reg, reset_bit);
}