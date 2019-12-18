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
struct iscsi_conn {int nopin_timer_flags; int /*<<< orphan*/  nopin_timer_lock; int /*<<< orphan*/  nopin_timer; } ;

/* Variables and functions */
 int ISCSI_TF_RUNNING ; 
 int ISCSI_TF_STOP ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void iscsit_stop_nopin_timer(struct iscsi_conn *conn)
{
	spin_lock_bh(&conn->nopin_timer_lock);
	if (!(conn->nopin_timer_flags & ISCSI_TF_RUNNING)) {
		spin_unlock_bh(&conn->nopin_timer_lock);
		return;
	}
	conn->nopin_timer_flags |= ISCSI_TF_STOP;
	spin_unlock_bh(&conn->nopin_timer_lock);

	del_timer_sync(&conn->nopin_timer);

	spin_lock_bh(&conn->nopin_timer_lock);
	conn->nopin_timer_flags &= ~ISCSI_TF_RUNNING;
	spin_unlock_bh(&conn->nopin_timer_lock);
}