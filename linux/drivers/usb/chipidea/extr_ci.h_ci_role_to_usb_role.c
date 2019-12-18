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
struct ci_hdrc {scalar_t__ role; scalar_t__ vbus_active; } ;
typedef  enum usb_role { ____Placeholder_usb_role } usb_role ;

/* Variables and functions */
 scalar_t__ CI_ROLE_GADGET ; 
 scalar_t__ CI_ROLE_HOST ; 
 int USB_ROLE_DEVICE ; 
 int USB_ROLE_HOST ; 
 int USB_ROLE_NONE ; 

__attribute__((used)) static inline enum usb_role ci_role_to_usb_role(struct ci_hdrc *ci)
{
	if (ci->role == CI_ROLE_HOST)
		return USB_ROLE_HOST;
	else if (ci->role == CI_ROLE_GADGET && ci->vbus_active)
		return USB_ROLE_DEVICE;
	else
		return USB_ROLE_NONE;
}