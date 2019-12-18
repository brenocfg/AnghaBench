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
struct ar9170 {int last_reason; int force_usb_reset; int /*<<< orphan*/  restart_work; int /*<<< orphan*/  hw; scalar_t__ needs_full_reset; int /*<<< orphan*/  registered; TYPE_1__* udev; int /*<<< orphan*/  pending_restarts; } ;
typedef  enum carl9170_restart_reasons { ____Placeholder_carl9170_restart_reasons } carl9170_restart_reasons ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARL9170_IDLE ; 
 int const CARL9170_RR_NO_REASON ; 
 int /*<<< orphan*/  CARL9170_STARTED ; 
 int /*<<< orphan*/  IS_ACCEPTING_CMD (struct ar9170*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int const __CARL9170_RR_LAST ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  carl9170_set_state_when (struct ar9170*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int const) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int const) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_stop_queues (int /*<<< orphan*/ ) ; 

void carl9170_restart(struct ar9170 *ar, const enum carl9170_restart_reasons r)
{
	carl9170_set_state_when(ar, CARL9170_STARTED, CARL9170_IDLE);

	/*
	 * Sometimes, an error can trigger several different reset events.
	 * By ignoring these *surplus* reset events, the device won't be
	 * killed again, right after it has recovered.
	 */
	if (atomic_inc_return(&ar->pending_restarts) > 1) {
		dev_dbg(&ar->udev->dev, "ignoring restart (%d)\n", r);
		return;
	}

	ieee80211_stop_queues(ar->hw);

	dev_err(&ar->udev->dev, "restart device (%d)\n", r);

	if (!WARN_ON(r == CARL9170_RR_NO_REASON) ||
	    !WARN_ON(r >= __CARL9170_RR_LAST))
		ar->last_reason = r;

	if (!ar->registered)
		return;

	if (!IS_ACCEPTING_CMD(ar) || ar->needs_full_reset)
		ar->force_usb_reset = true;

	ieee80211_queue_work(ar->hw, &ar->restart_work);

	/*
	 * At this point, the device instance might have vanished/disabled.
	 * So, don't put any code which access the ar9170 struct
	 * without proper protection.
	 */
}