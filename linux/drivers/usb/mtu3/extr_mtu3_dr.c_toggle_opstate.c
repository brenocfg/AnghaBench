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
struct TYPE_2__ {int /*<<< orphan*/  is_u3_drd; } ;
struct ssusb_mtk {int /*<<< orphan*/  mac_base; TYPE_1__ otg_switch; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_SESSION ; 
 int /*<<< orphan*/  SOFT_CONN ; 
 int /*<<< orphan*/  U3D_DEVICE_CONTROL ; 
 int /*<<< orphan*/  U3D_POWER_MANAGEMENT ; 
 int /*<<< orphan*/  mtu3_setbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void toggle_opstate(struct ssusb_mtk *ssusb)
{
	if (!ssusb->otg_switch.is_u3_drd) {
		mtu3_setbits(ssusb->mac_base, U3D_DEVICE_CONTROL, DC_SESSION);
		mtu3_setbits(ssusb->mac_base, U3D_POWER_MANAGEMENT, SOFT_CONN);
	}
}