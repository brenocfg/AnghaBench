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
struct TYPE_2__ {int /*<<< orphan*/  recv_channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hv_poll_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvp_host_handshake_work ; 
 int /*<<< orphan*/  kvp_poll_wrapper ; 
 TYPE_1__ kvp_transaction ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static void kvp_register_done(void)
{
	/*
	 * If we're still negotiating with the host cancel the timeout
	 * work to not poll the channel twice.
	 */
	pr_debug("KVP: userspace daemon registered\n");
	cancel_delayed_work_sync(&kvp_host_handshake_work);
	hv_poll_channel(kvp_transaction.recv_channel, kvp_poll_wrapper);
}