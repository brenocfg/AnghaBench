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
typedef  int u32 ;
struct nbu2ss_udc {TYPE_1__* p_regs; } ;
typedef  enum usb_device_speed { ____Placeholder_usb_device_speed } usb_device_speed ;
struct TYPE_2__ {int /*<<< orphan*/  USB_STATUS; } ;

/* Variables and functions */
 int HIGH_SPEED ; 
 int USB_SPEED_FULL ; 
 int USB_SPEED_HIGH ; 
 int _nbu2ss_readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline enum usb_device_speed _nbu2ss_get_speed(struct nbu2ss_udc *udc)
{
	u32		data;
	enum usb_device_speed speed = USB_SPEED_FULL;

	data = _nbu2ss_readl(&udc->p_regs->USB_STATUS);
	if (data & HIGH_SPEED)
		speed = USB_SPEED_HIGH;

	return speed;
}