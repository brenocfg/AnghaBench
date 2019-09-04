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
struct axp288_extcon_info {int /*<<< orphan*/  role_sw; scalar_t__ id_extcon; } ;
typedef  enum usb_role { ____Placeholder_usb_role } usb_role ;

/* Variables and functions */
 int /*<<< orphan*/  EXTCON_USB_HOST ; 
 int USB_ROLE_HOST ; 
 scalar_t__ extcon_get_state (scalar_t__,int /*<<< orphan*/ ) ; 
 int usb_role_switch_get_role (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool axp288_get_id_pin(struct axp288_extcon_info *info)
{
	enum usb_role role;

	if (info->id_extcon)
		return extcon_get_state(info->id_extcon, EXTCON_USB_HOST) <= 0;

	/* We cannot access the id-pin, see what mode the AML code has set */
	role = usb_role_switch_get_role(info->role_sw);
	return role != USB_ROLE_HOST;
}