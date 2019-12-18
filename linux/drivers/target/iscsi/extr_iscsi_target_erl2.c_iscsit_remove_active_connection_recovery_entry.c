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
struct iscsi_session {int /*<<< orphan*/  cr_a_lock; int /*<<< orphan*/  sid; int /*<<< orphan*/  conn_recovery_count; } ;
struct iscsi_conn_recovery {int /*<<< orphan*/  cr_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct iscsi_conn_recovery*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int iscsit_remove_active_connection_recovery_entry(
	struct iscsi_conn_recovery *cr,
	struct iscsi_session *sess)
{
	spin_lock(&sess->cr_a_lock);
	list_del(&cr->cr_list);

	sess->conn_recovery_count--;
	pr_debug("Decremented connection recovery count to %u for"
		" SID: %u\n", sess->conn_recovery_count, sess->sid);
	spin_unlock(&sess->cr_a_lock);

	kfree(cr);

	return 0;
}