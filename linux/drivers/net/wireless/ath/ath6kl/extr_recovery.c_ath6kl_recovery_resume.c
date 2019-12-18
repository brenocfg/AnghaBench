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
struct TYPE_2__ {int hb_pending; int /*<<< orphan*/  hb_poll; int /*<<< orphan*/  hb_timer; scalar_t__ hb_misscnt; scalar_t__ seq_num; int /*<<< orphan*/  enable; } ;
struct ath6kl {TYPE_1__ fw_recovery; int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  RECOVERY_CLEANUP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

void ath6kl_recovery_resume(struct ath6kl *ar)
{
	if (!ar->fw_recovery.enable)
		return;

	clear_bit(RECOVERY_CLEANUP, &ar->flag);

	if (!ar->fw_recovery.hb_poll)
		return;

	ar->fw_recovery.hb_pending = false;
	ar->fw_recovery.seq_num = 0;
	ar->fw_recovery.hb_misscnt = 0;
	mod_timer(&ar->fw_recovery.hb_timer,
		  jiffies + msecs_to_jiffies(ar->fw_recovery.hb_poll));
}