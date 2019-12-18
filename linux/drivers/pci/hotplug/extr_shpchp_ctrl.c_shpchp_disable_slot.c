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
typedef  scalar_t__ u8 ;
struct slot {struct controller* ctrl; TYPE_1__* hpc_ops; } ;
struct controller {int /*<<< orphan*/  crit_sect; } ;
struct TYPE_2__ {int (* get_adapter_status ) (struct slot*,scalar_t__*) ;int (* get_latch_status ) (struct slot*,scalar_t__*) ;int (* get_power_status ) (struct slot*,scalar_t__*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ctrl_info (struct controller*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int remove_board (struct slot*) ; 
 int /*<<< orphan*/  slot_name (struct slot*) ; 
 int stub1 (struct slot*,scalar_t__*) ; 
 int stub2 (struct slot*,scalar_t__*) ; 
 int stub3 (struct slot*,scalar_t__*) ; 
 int /*<<< orphan*/  update_slot_info (struct slot*) ; 

__attribute__((used)) static int shpchp_disable_slot (struct slot *p_slot)
{
	u8 getstatus = 0;
	int rc, retval = -ENODEV;
	struct controller *ctrl = p_slot->ctrl;

	if (!p_slot->ctrl)
		return -ENODEV;

	/* Check to see if (latch closed, card present, power on) */
	mutex_lock(&p_slot->ctrl->crit_sect);

	rc = p_slot->hpc_ops->get_adapter_status(p_slot, &getstatus);
	if (rc || !getstatus) {
		ctrl_info(ctrl, "No adapter on slot(%s)\n", slot_name(p_slot));
		goto out;
	}
	rc = p_slot->hpc_ops->get_latch_status(p_slot, &getstatus);
	if (rc || getstatus) {
		ctrl_info(ctrl, "Latch open on slot(%s)\n", slot_name(p_slot));
		goto out;
	}
	rc = p_slot->hpc_ops->get_power_status(p_slot, &getstatus);
	if (rc || !getstatus) {
		ctrl_info(ctrl, "Already disabled on slot(%s)\n",
			  slot_name(p_slot));
		goto out;
	}

	retval = remove_board(p_slot);
	update_slot_info(p_slot);
 out:
	mutex_unlock(&p_slot->ctrl->crit_sect);
	return retval;
}