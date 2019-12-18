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
struct usbhs_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  usbhs_sys_function_pullup (struct usbhs_priv*,int) ; 
 scalar_t__ usbhsg_can_pullup (struct usbhs_priv*) ; 

__attribute__((used)) static void usbhsg_update_pullup(struct usbhs_priv *priv)
{
	if (usbhsg_can_pullup(priv))
		usbhs_sys_function_pullup(priv, 1);
	else
		usbhs_sys_function_pullup(priv, 0);
}