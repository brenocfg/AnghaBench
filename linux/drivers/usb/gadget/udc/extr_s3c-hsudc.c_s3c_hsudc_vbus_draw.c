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
struct usb_gadget {int dummy; } ;
struct s3c_hsudc {int /*<<< orphan*/  transceiver; } ;

/* Variables and functions */
 int ENODEV ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 struct s3c_hsudc* to_hsudc (struct usb_gadget*) ; 
 int usb_phy_set_power (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int s3c_hsudc_vbus_draw(struct usb_gadget *gadget, unsigned mA)
{
	struct s3c_hsudc *hsudc = to_hsudc(gadget);

	if (!hsudc)
		return -ENODEV;

	if (!IS_ERR_OR_NULL(hsudc->transceiver))
		return usb_phy_set_power(hsudc->transceiver, mA);

	return -EOPNOTSUPP;
}