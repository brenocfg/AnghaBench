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
struct fm10k_intfc {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __FM10K_RESETTING ; 
 int /*<<< orphan*/  fm10k_iov_mbx (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_watchdog_update_host_state (struct fm10k_intfc*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm10k_mbx_subtask(struct fm10k_intfc *interface)
{
	/* If we're resetting, bail out */
	if (test_bit(__FM10K_RESETTING, interface->state))
		return;

	/* process upstream mailbox and update device state */
	fm10k_watchdog_update_host_state(interface);

	/* process downstream mailboxes */
	fm10k_iov_mbx(interface);
}