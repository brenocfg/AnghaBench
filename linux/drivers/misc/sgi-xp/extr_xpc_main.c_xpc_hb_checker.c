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
struct TYPE_2__ {int /*<<< orphan*/  (* process_activate_IRQ_rcvd ) () ;} ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  XPC_HB_CHECK_CPU ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_of (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  set_cpus_allowed_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 scalar_t__ time_is_before_eq_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 
 scalar_t__ xpc_activate_IRQ_rcvd ; 
 int /*<<< orphan*/  xpc_activate_IRQ_wq ; 
 TYPE_1__ xpc_arch_ops ; 
 int /*<<< orphan*/  xpc_check_remote_hb () ; 
 scalar_t__ xpc_exiting ; 
 int xpc_hb_check_interval ; 
 scalar_t__ xpc_hb_check_timeout ; 
 int /*<<< orphan*/  xpc_hb_checker_exited ; 
 int /*<<< orphan*/  xpc_part ; 
 int /*<<< orphan*/  xpc_start_hb_beater () ; 
 int /*<<< orphan*/  xpc_stop_hb_beater () ; 

__attribute__((used)) static int
xpc_hb_checker(void *ignore)
{
	int force_IRQ = 0;

	/* this thread was marked active by xpc_hb_init() */

	set_cpus_allowed_ptr(current, cpumask_of(XPC_HB_CHECK_CPU));

	/* set our heartbeating to other partitions into motion */
	xpc_hb_check_timeout = jiffies + (xpc_hb_check_interval * HZ);
	xpc_start_hb_beater();

	while (!xpc_exiting) {

		dev_dbg(xpc_part, "woke up with %d ticks rem; %d IRQs have "
			"been received\n",
			(int)(xpc_hb_check_timeout - jiffies),
			xpc_activate_IRQ_rcvd);

		/* checking of remote heartbeats is skewed by IRQ handling */
		if (time_is_before_eq_jiffies(xpc_hb_check_timeout)) {
			xpc_hb_check_timeout = jiffies +
			    (xpc_hb_check_interval * HZ);

			dev_dbg(xpc_part, "checking remote heartbeats\n");
			xpc_check_remote_hb();
		}

		/* check for outstanding IRQs */
		if (xpc_activate_IRQ_rcvd > 0 || force_IRQ != 0) {
			force_IRQ = 0;
			dev_dbg(xpc_part, "processing activate IRQs "
				"received\n");
			xpc_arch_ops.process_activate_IRQ_rcvd();
		}

		/* wait for IRQ or timeout */
		(void)wait_event_interruptible(xpc_activate_IRQ_wq,
					       (time_is_before_eq_jiffies(
						xpc_hb_check_timeout) ||
						xpc_activate_IRQ_rcvd > 0 ||
						xpc_exiting));
	}

	xpc_stop_hb_beater();

	dev_dbg(xpc_part, "heartbeat checker is exiting\n");

	/* mark this thread as having exited */
	complete(&xpc_hb_checker_exited);
	return 0;
}