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
struct usb_device_id {scalar_t__ idProduct; } ;

/* Variables and functions */
 scalar_t__ USB_MEMORATOR_PRODUCT_ID ; 
 scalar_t__ USB_USBCAN_REVB_PRODUCT_ID ; 

__attribute__((used)) static inline bool kvaser_is_usbcan(const struct usb_device_id *id)
{
	return id->idProduct >= USB_USBCAN_REVB_PRODUCT_ID &&
	       id->idProduct <= USB_MEMORATOR_PRODUCT_ID;
}