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
struct iscsi_tpg_np {int /*<<< orphan*/  tpg_np_comp; int /*<<< orphan*/  tpg_np_kref; } ;
struct iscsi_portal_group {int dummy; } ;
struct iscsi_np {scalar_t__ np_thread_state; int /*<<< orphan*/  np_thread_lock; int /*<<< orphan*/  np_restart_comp; scalar_t__ np_thread; int /*<<< orphan*/  np_reset_count; } ;

/* Variables and functions */
 scalar_t__ ISCSI_NP_THREAD_INACTIVE ; 
 scalar_t__ ISCSI_NP_THREAD_RESET ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsit_login_kref_put ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int iscsit_reset_np_thread(
	struct iscsi_np *np,
	struct iscsi_tpg_np *tpg_np,
	struct iscsi_portal_group *tpg,
	bool shutdown)
{
	spin_lock_bh(&np->np_thread_lock);
	if (np->np_thread_state == ISCSI_NP_THREAD_INACTIVE) {
		spin_unlock_bh(&np->np_thread_lock);
		return 0;
	}
	np->np_thread_state = ISCSI_NP_THREAD_RESET;
	atomic_inc(&np->np_reset_count);

	if (np->np_thread) {
		spin_unlock_bh(&np->np_thread_lock);
		send_sig(SIGINT, np->np_thread, 1);
		wait_for_completion(&np->np_restart_comp);
		spin_lock_bh(&np->np_thread_lock);
	}
	spin_unlock_bh(&np->np_thread_lock);

	if (tpg_np && shutdown) {
		kref_put(&tpg_np->tpg_np_kref, iscsit_login_kref_put);

		wait_for_completion(&tpg_np->tpg_np_comp);
	}

	return 0;
}