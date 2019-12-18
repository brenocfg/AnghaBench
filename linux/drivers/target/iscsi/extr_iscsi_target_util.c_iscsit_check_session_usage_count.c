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
struct iscsi_session {scalar_t__ session_usage_count; int session_waiting_on_uc; int /*<<< orphan*/  session_usage_lock; int /*<<< orphan*/  session_waiting_on_uc_comp; } ;

/* Variables and functions */
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int iscsit_check_session_usage_count(struct iscsi_session *sess)
{
	spin_lock_bh(&sess->session_usage_lock);
	if (sess->session_usage_count != 0) {
		sess->session_waiting_on_uc = 1;
		spin_unlock_bh(&sess->session_usage_lock);
		if (in_interrupt())
			return 2;

		wait_for_completion(&sess->session_waiting_on_uc_comp);
		return 1;
	}
	spin_unlock_bh(&sess->session_usage_lock);

	return 0;
}