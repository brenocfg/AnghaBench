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
struct iscsi_node_attrib {int nopin_response_timeout; } ;
struct iscsi_conn {int nopin_response_timer_flags; int /*<<< orphan*/  nopin_timer_lock; int /*<<< orphan*/  cid; int /*<<< orphan*/  nopin_response_timer; struct iscsi_session* sess; } ;

/* Variables and functions */
 int HZ ; 
 int ISCSI_TF_RUNNING ; 
 int ISCSI_TF_STOP ; 
 struct iscsi_node_attrib* iscsit_tpg_get_node_attrib (struct iscsi_session*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void iscsit_start_nopin_response_timer(struct iscsi_conn *conn)
{
	struct iscsi_session *sess = conn->sess;
	struct iscsi_node_attrib *na = iscsit_tpg_get_node_attrib(sess);

	spin_lock_bh(&conn->nopin_timer_lock);
	if (conn->nopin_response_timer_flags & ISCSI_TF_RUNNING) {
		spin_unlock_bh(&conn->nopin_timer_lock);
		return;
	}

	conn->nopin_response_timer_flags &= ~ISCSI_TF_STOP;
	conn->nopin_response_timer_flags |= ISCSI_TF_RUNNING;
	mod_timer(&conn->nopin_response_timer,
		  jiffies + na->nopin_response_timeout * HZ);

	pr_debug("Started NOPIN Response Timer on CID: %d to %u"
		" seconds\n", conn->cid, na->nopin_response_timeout);
	spin_unlock_bh(&conn->nopin_timer_lock);
}