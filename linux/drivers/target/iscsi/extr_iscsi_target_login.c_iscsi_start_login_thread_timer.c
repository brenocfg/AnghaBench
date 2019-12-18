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
struct iscsi_np {int /*<<< orphan*/  np_thread_lock; int /*<<< orphan*/  np_login_timer; int /*<<< orphan*/  np_login_timer_flags; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  ISCSI_TF_RUNNING ; 
 int /*<<< orphan*/  ISCSI_TF_STOP ; 
 int TA_LOGIN_TIMEOUT ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iscsi_start_login_thread_timer(struct iscsi_np *np)
{
	/*
	 * This used the TA_LOGIN_TIMEOUT constant because at this
	 * point we do not have access to ISCSI_TPG_ATTRIB(tpg)->login_timeout
	 */
	spin_lock_bh(&np->np_thread_lock);
	np->np_login_timer_flags &= ~ISCSI_TF_STOP;
	np->np_login_timer_flags |= ISCSI_TF_RUNNING;
	mod_timer(&np->np_login_timer, jiffies + TA_LOGIN_TIMEOUT * HZ);

	pr_debug("Added timeout timer to iSCSI login request for"
			" %u seconds.\n", TA_LOGIN_TIMEOUT);
	spin_unlock_bh(&np->np_thread_lock);
}