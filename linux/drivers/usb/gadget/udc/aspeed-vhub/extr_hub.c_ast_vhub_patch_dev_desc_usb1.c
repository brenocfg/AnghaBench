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
struct usb_device_descriptor {scalar_t__ bDeviceProtocol; int /*<<< orphan*/  bcdUSB; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int) ; 

__attribute__((used)) static void ast_vhub_patch_dev_desc_usb1(struct usb_device_descriptor *desc)
{
	desc->bcdUSB = cpu_to_le16(0x0100);
	desc->bDeviceProtocol = 0;
}