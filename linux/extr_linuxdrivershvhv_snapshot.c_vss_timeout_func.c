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
struct work_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  recv_channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  HV_E_FAIL ; 
 int /*<<< orphan*/  hv_poll_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  vss_poll_wrapper ; 
 int /*<<< orphan*/  vss_respond_to_host (int /*<<< orphan*/ ) ; 
 TYPE_1__ vss_transaction ; 

__attribute__((used)) static void vss_timeout_func(struct work_struct *dummy)
{
	/*
	 * Timeout waiting for userspace component to reply happened.
	 */
	pr_warn("VSS: timeout waiting for daemon to reply\n");
	vss_respond_to_host(HV_E_FAIL);

	hv_poll_channel(vss_transaction.recv_channel, vss_poll_wrapper);
}