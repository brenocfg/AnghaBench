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
struct otg_switch_mtk {int /*<<< orphan*/  role_sw; int /*<<< orphan*/  vbus_work; int /*<<< orphan*/  id_work; } ;
struct ssusb_mtk {struct otg_switch_mtk otg_switch; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_role_switch_unregister (int /*<<< orphan*/ ) ; 

void ssusb_otg_switch_exit(struct ssusb_mtk *ssusb)
{
	struct otg_switch_mtk *otg_sx = &ssusb->otg_switch;

	cancel_work_sync(&otg_sx->id_work);
	cancel_work_sync(&otg_sx->vbus_work);
	usb_role_switch_unregister(otg_sx->role_sw);
}