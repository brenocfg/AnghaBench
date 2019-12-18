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
struct otg_switch_mtk {scalar_t__ role_sw_used; scalar_t__ manual_drd_enabled; int /*<<< orphan*/  vbus_work; int /*<<< orphan*/  id_work; } ;
struct ssusb_mtk {struct otg_switch_mtk otg_switch; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssusb_dr_debugfs_init (struct ssusb_mtk*) ; 
 int ssusb_extcon_register (struct otg_switch_mtk*) ; 
 int /*<<< orphan*/  ssusb_id_work ; 
 int ssusb_role_sw_register (struct otg_switch_mtk*) ; 
 int /*<<< orphan*/  ssusb_vbus_work ; 

int ssusb_otg_switch_init(struct ssusb_mtk *ssusb)
{
	struct otg_switch_mtk *otg_sx = &ssusb->otg_switch;
	int ret = 0;

	INIT_WORK(&otg_sx->id_work, ssusb_id_work);
	INIT_WORK(&otg_sx->vbus_work, ssusb_vbus_work);

	if (otg_sx->manual_drd_enabled)
		ssusb_dr_debugfs_init(ssusb);
	else if (otg_sx->role_sw_used)
		ret = ssusb_role_sw_register(otg_sx);
	else
		ret = ssusb_extcon_register(otg_sx);

	return ret;
}