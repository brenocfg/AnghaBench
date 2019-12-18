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
struct TYPE_2__ {int /*<<< orphan*/  recovery_work; int /*<<< orphan*/  hb_timer; int /*<<< orphan*/  enable; } ;
struct ath6kl {TYPE_1__ fw_recovery; int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  RECOVERY_CLEANUP ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ath6kl_recovery_cleanup(struct ath6kl *ar)
{
	if (!ar->fw_recovery.enable)
		return;

	set_bit(RECOVERY_CLEANUP, &ar->flag);

	del_timer_sync(&ar->fw_recovery.hb_timer);
	cancel_work_sync(&ar->fw_recovery.recovery_work);
}