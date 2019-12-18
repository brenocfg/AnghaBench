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
struct TYPE_2__ {scalar_t__ err_reason; int /*<<< orphan*/  enable; } ;
struct ath6kl {scalar_t__ state; TYPE_1__ fw_recovery; } ;

/* Variables and functions */
 scalar_t__ ATH6KL_STATE_ON ; 
 scalar_t__ ATH6KL_STATE_RECOVERY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ath6kl_init_hw_restart (struct ath6kl*) ; 
 int /*<<< orphan*/  ath6kl_recovery_cleanup (struct ath6kl*) ; 

void ath6kl_recovery_suspend(struct ath6kl *ar)
{
	if (!ar->fw_recovery.enable)
		return;

	ath6kl_recovery_cleanup(ar);

	if (!ar->fw_recovery.err_reason)
		return;

	/* Process pending fw error detection */
	ar->fw_recovery.err_reason = 0;
	WARN_ON(ar->state != ATH6KL_STATE_ON);
	ar->state = ATH6KL_STATE_RECOVERY;
	ath6kl_init_hw_restart(ar);
	ar->state = ATH6KL_STATE_ON;
}