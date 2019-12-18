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
struct ath6kl_vif {int /*<<< orphan*/  flags; } ;
struct ath6kl {int /*<<< orphan*/  sem; int /*<<< orphan*/  event_wq; int /*<<< orphan*/  wmi; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  STATS_UPDATE_PEND ; 
 int /*<<< orphan*/  WMI_TIMEOUT ; 
 scalar_t__ ath6kl_wmi_get_stats_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int ath6kl_read_tgt_stats(struct ath6kl *ar, struct ath6kl_vif *vif)
{
	long left;

	if (down_interruptible(&ar->sem))
		return -EBUSY;

	set_bit(STATS_UPDATE_PEND, &vif->flags);

	if (ath6kl_wmi_get_stats_cmd(ar->wmi, 0)) {
		up(&ar->sem);
		return -EIO;
	}

	left = wait_event_interruptible_timeout(ar->event_wq,
						!test_bit(STATS_UPDATE_PEND,
						&vif->flags), WMI_TIMEOUT);

	up(&ar->sem);

	if (left <= 0)
		return -ETIMEDOUT;

	return 0;
}