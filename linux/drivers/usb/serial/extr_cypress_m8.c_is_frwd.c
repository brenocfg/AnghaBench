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
struct TYPE_2__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {TYPE_1__ descriptor; } ;

/* Variables and functions */
 scalar_t__ PRODUCT_ID_CYPHIDCOM_FRWD ; 
 scalar_t__ VENDOR_ID_FRWD ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool is_frwd(struct usb_device *dev)
{
	return ((le16_to_cpu(dev->descriptor.idVendor) == VENDOR_ID_FRWD) &&
		(le16_to_cpu(dev->descriptor.idProduct) == PRODUCT_ID_CYPHIDCOM_FRWD));
}