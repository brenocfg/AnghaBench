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

/* Variables and functions */
 int ENODEV ; 
 int IPMI_SET_TIMEOUT_FORCE_HB ; 
 int IPMI_SET_TIMEOUT_HB_IF_NECESSARY ; 
 int __ipmi_heartbeat () ; 
 int __ipmi_set_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_tofree ; 
 int /*<<< orphan*/  msg_wait ; 
 int /*<<< orphan*/  recv_msg ; 
 int /*<<< orphan*/  smi_msg ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_user ; 

__attribute__((used)) static int _ipmi_set_timeout(int do_heartbeat)
{
	int send_heartbeat_now;
	int rv;

	if (!watchdog_user)
		return -ENODEV;

	atomic_set(&msg_tofree, 2);

	rv = __ipmi_set_timeout(&smi_msg,
				&recv_msg,
				&send_heartbeat_now);
	if (rv)
		return rv;

	wait_for_completion(&msg_wait);

	if ((do_heartbeat == IPMI_SET_TIMEOUT_FORCE_HB)
		|| ((send_heartbeat_now)
		    && (do_heartbeat == IPMI_SET_TIMEOUT_HB_IF_NECESSARY)))
		rv = __ipmi_heartbeat();

	return rv;
}