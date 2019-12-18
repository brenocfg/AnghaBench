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
typedef  scalar_t__ u32 ;
struct phy {int dummy; } ;

/* Variables and functions */
 scalar_t__ ISCR_FORCE_VBUS_HIGH ; 
 scalar_t__ ISCR_FORCE_VBUS_LOW ; 
 int /*<<< orphan*/  ISCR_FORCE_VBUS_MASK ; 
 int /*<<< orphan*/  sun4i_usb_phy0_update_iscr (struct phy*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sun4i_usb_phy0_set_vbus_detect(struct phy *phy, u32 val)
{
	if (val)
		val = ISCR_FORCE_VBUS_HIGH;
	else
		val = ISCR_FORCE_VBUS_LOW;

	sun4i_usb_phy0_update_iscr(phy, ISCR_FORCE_VBUS_MASK, val);
}