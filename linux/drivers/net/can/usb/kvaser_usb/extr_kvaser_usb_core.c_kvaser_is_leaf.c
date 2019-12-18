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
 scalar_t__ USB_CAN_R_PRODUCT_ID ; 
 scalar_t__ USB_LEAF_DEVEL_PRODUCT_ID ; 
 scalar_t__ USB_LEAF_LITE_V2_PRODUCT_ID ; 
 scalar_t__ USB_MINI_PCIE_2HS_PRODUCT_ID ; 

__attribute__((used)) static inline bool kvaser_is_leaf(const struct usb_device_id *id)
{
	return (id->idProduct >= USB_LEAF_DEVEL_PRODUCT_ID &&
		id->idProduct <= USB_CAN_R_PRODUCT_ID) ||
		(id->idProduct >= USB_LEAF_LITE_V2_PRODUCT_ID &&
		 id->idProduct <= USB_MINI_PCIE_2HS_PRODUCT_ID);
}