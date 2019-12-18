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
struct tb {int /*<<< orphan*/  wq; int /*<<< orphan*/  root_switch; TYPE_1__* nhi; } ;
struct icm {int /*<<< orphan*/  rescan_work; } ;
struct TYPE_2__ {scalar_t__ going_away; } ;

/* Variables and functions */
 int /*<<< orphan*/  __icm_driver_ready (struct tb*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  icm_unplug_children (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icm_veto_end (struct tb*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct icm* tb_priv (struct tb*) ; 

__attribute__((used)) static void icm_complete(struct tb *tb)
{
	struct icm *icm = tb_priv(tb);

	if (tb->nhi->going_away)
		return;

	/*
	 * If RTD3 was vetoed before we entered system suspend allow it
	 * again now before driver ready is sent. Firmware sends a new RTD3
	 * veto if it is still the case after we have sent it driver ready
	 * command.
	 */
	icm_veto_end(tb);
	icm_unplug_children(tb->root_switch);

	/*
	 * Now all existing children should be resumed, start events
	 * from ICM to get updated status.
	 */
	__icm_driver_ready(tb, NULL, NULL, NULL);

	/*
	 * We do not get notifications of devices that have been
	 * unplugged during suspend so schedule rescan to clean them up
	 * if any.
	 */
	queue_delayed_work(tb->wq, &icm->rescan_work, msecs_to_jiffies(500));
}