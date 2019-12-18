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
struct ath6kl_fw_recovery {int hb_pending; scalar_t__ hb_poll; int /*<<< orphan*/  hb_timer; scalar_t__ hb_misscnt; scalar_t__ seq_num; int /*<<< orphan*/  recovery_work; } ;
struct ath6kl {struct ath6kl_fw_recovery fw_recovery; int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RECOVERY_CLEANUP ; 
 int /*<<< orphan*/  TIMER_DEFERRABLE ; 
 int /*<<< orphan*/  ath6kl_recovery_hb_timer ; 
 int /*<<< orphan*/  ath6kl_recovery_work ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ath6kl_recovery_init(struct ath6kl *ar)
{
	struct ath6kl_fw_recovery *recovery = &ar->fw_recovery;

	clear_bit(RECOVERY_CLEANUP, &ar->flag);
	INIT_WORK(&recovery->recovery_work, ath6kl_recovery_work);
	recovery->seq_num = 0;
	recovery->hb_misscnt = 0;
	ar->fw_recovery.hb_pending = false;
	timer_setup(&ar->fw_recovery.hb_timer, ath6kl_recovery_hb_timer,
		    TIMER_DEFERRABLE);

	if (ar->fw_recovery.hb_poll)
		mod_timer(&ar->fw_recovery.hb_timer, jiffies +
			  msecs_to_jiffies(ar->fw_recovery.hb_poll));
}