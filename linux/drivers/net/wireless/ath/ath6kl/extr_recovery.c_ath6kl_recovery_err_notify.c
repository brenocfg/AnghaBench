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
struct TYPE_2__ {int /*<<< orphan*/  recovery_work; int /*<<< orphan*/  err_reason; int /*<<< orphan*/  enable; } ;
struct ath6kl {scalar_t__ state; TYPE_1__ fw_recovery; int /*<<< orphan*/  ath6kl_wq; int /*<<< orphan*/  flag; } ;
typedef  enum ath6kl_fw_err { ____Placeholder_ath6kl_fw_err } ath6kl_fw_err ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_RECOVERY ; 
 scalar_t__ ATH6KL_STATE_RECOVERY ; 
 int /*<<< orphan*/  RECOVERY_CLEANUP ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ath6kl_recovery_err_notify(struct ath6kl *ar, enum ath6kl_fw_err reason)
{
	if (!ar->fw_recovery.enable)
		return;

	ath6kl_dbg(ATH6KL_DBG_RECOVERY, "Fw error detected, reason:%d\n",
		   reason);

	set_bit(reason, &ar->fw_recovery.err_reason);

	if (!test_bit(RECOVERY_CLEANUP, &ar->flag) &&
	    ar->state != ATH6KL_STATE_RECOVERY)
		queue_work(ar->ath6kl_wq, &ar->fw_recovery.recovery_work);
}