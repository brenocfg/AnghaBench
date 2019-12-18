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
struct iscsi_conn {int /*<<< orphan*/  nopin_timer_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __iscsit_start_nopin_timer (struct iscsi_conn*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void iscsit_start_nopin_timer(struct iscsi_conn *conn)
{
	spin_lock_bh(&conn->nopin_timer_lock);
	__iscsit_start_nopin_timer(conn);
	spin_unlock_bh(&conn->nopin_timer_lock);
}