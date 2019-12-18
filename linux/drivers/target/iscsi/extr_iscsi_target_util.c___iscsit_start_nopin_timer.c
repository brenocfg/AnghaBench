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
struct iscsi_session {int dummy; } ;
struct iscsi_node_attrib {int nopin_timeout; } ;
struct iscsi_conn {int nopin_timer_flags; int /*<<< orphan*/  cid; int /*<<< orphan*/  nopin_timer; int /*<<< orphan*/  nopin_timer_lock; struct iscsi_session* sess; } ;

/* Variables and functions */
 int HZ ; 
 int ISCSI_TF_RUNNING ; 
 int ISCSI_TF_STOP ; 
 struct iscsi_node_attrib* iscsit_tpg_get_node_attrib (struct iscsi_session*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 

void __iscsit_start_nopin_timer(struct iscsi_conn *conn)
{
	struct iscsi_session *sess = conn->sess;
	struct iscsi_node_attrib *na = iscsit_tpg_get_node_attrib(sess);

	lockdep_assert_held(&conn->nopin_timer_lock);

	/*
	* NOPIN timeout is disabled.
	 */
	if (!na->nopin_timeout)
		return;

	if (conn->nopin_timer_flags & ISCSI_TF_RUNNING)
		return;

	conn->nopin_timer_flags &= ~ISCSI_TF_STOP;
	conn->nopin_timer_flags |= ISCSI_TF_RUNNING;
	mod_timer(&conn->nopin_timer, jiffies + na->nopin_timeout * HZ);

	pr_debug("Started NOPIN Timer on CID: %d at %u second"
		" interval\n", conn->cid, na->nopin_timeout);
}