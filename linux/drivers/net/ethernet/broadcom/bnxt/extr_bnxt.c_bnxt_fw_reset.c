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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ active_vfs; } ;
struct bnxt {scalar_t__ fw_reset_max_dsecs; int fw_cap; int fw_reset_min_dsecs; int /*<<< orphan*/  fw_reset_state; int /*<<< orphan*/  dev; int /*<<< orphan*/  state; TYPE_1__ pf; } ;

/* Variables and functions */
 int BNXT_FW_CAP_ERR_RECOVER_RELOAD ; 
 int /*<<< orphan*/  BNXT_FW_RESET_STATE_ENABLE_DEV ; 
 int /*<<< orphan*/  BNXT_FW_RESET_STATE_POLL_FW_DOWN ; 
 int /*<<< orphan*/  BNXT_FW_RESET_STATE_POLL_VF ; 
 int /*<<< orphan*/  BNXT_STATE_FW_FATAL_COND ; 
 int /*<<< orphan*/  BNXT_STATE_IN_FW_RESET ; 
 int /*<<< orphan*/  BNXT_STATE_OPEN ; 
 int HZ ; 
 int /*<<< orphan*/  bnxt_fw_reset_close (struct bnxt*) ; 
 int bnxt_get_registered_vfs (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_queue_fw_reset_work (struct bnxt*,int) ; 
 int /*<<< orphan*/  bnxt_rtnl_lock_sp (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_rtnl_unlock_sp (struct bnxt*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void bnxt_fw_reset(struct bnxt *bp)
{
	bnxt_rtnl_lock_sp(bp);
	if (test_bit(BNXT_STATE_OPEN, &bp->state) &&
	    !test_bit(BNXT_STATE_IN_FW_RESET, &bp->state)) {
		int n = 0, tmo;

		set_bit(BNXT_STATE_IN_FW_RESET, &bp->state);
		if (bp->pf.active_vfs &&
		    !test_bit(BNXT_STATE_FW_FATAL_COND, &bp->state))
			n = bnxt_get_registered_vfs(bp);
		if (n < 0) {
			netdev_err(bp->dev, "Firmware reset aborted, rc = %d\n",
				   n);
			clear_bit(BNXT_STATE_IN_FW_RESET, &bp->state);
			dev_close(bp->dev);
			goto fw_reset_exit;
		} else if (n > 0) {
			u16 vf_tmo_dsecs = n * 10;

			if (bp->fw_reset_max_dsecs < vf_tmo_dsecs)
				bp->fw_reset_max_dsecs = vf_tmo_dsecs;
			bp->fw_reset_state =
				BNXT_FW_RESET_STATE_POLL_VF;
			bnxt_queue_fw_reset_work(bp, HZ / 10);
			goto fw_reset_exit;
		}
		bnxt_fw_reset_close(bp);
		if (bp->fw_cap & BNXT_FW_CAP_ERR_RECOVER_RELOAD) {
			bp->fw_reset_state = BNXT_FW_RESET_STATE_POLL_FW_DOWN;
			tmo = HZ / 10;
		} else {
			bp->fw_reset_state = BNXT_FW_RESET_STATE_ENABLE_DEV;
			tmo = bp->fw_reset_min_dsecs * HZ / 10;
		}
		bnxt_queue_fw_reset_work(bp, tmo);
	}
fw_reset_exit:
	bnxt_rtnl_unlock_sp(bp);
}