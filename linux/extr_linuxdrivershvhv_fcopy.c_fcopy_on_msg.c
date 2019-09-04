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
struct TYPE_2__ {scalar_t__ state; int /*<<< orphan*/  recv_channel; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HVUTIL_DEVICE_INIT ; 
 scalar_t__ HVUTIL_USERSPACE_RECV ; 
 scalar_t__ HVUTIL_USERSPACE_REQ ; 
 scalar_t__ cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int fcopy_handle_handshake (int) ; 
 int /*<<< orphan*/  fcopy_poll_wrapper ; 
 int /*<<< orphan*/  fcopy_respond_to_host (int) ; 
 int /*<<< orphan*/  fcopy_timeout_work ; 
 TYPE_1__ fcopy_transaction ; 
 int /*<<< orphan*/  hv_poll_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fcopy_on_msg(void *msg, int len)
{
	int *val = (int *)msg;

	if (len != sizeof(int))
		return -EINVAL;

	if (fcopy_transaction.state == HVUTIL_DEVICE_INIT)
		return fcopy_handle_handshake(*val);

	if (fcopy_transaction.state != HVUTIL_USERSPACE_REQ)
		return -EINVAL;

	/*
	 * Complete the transaction by forwarding the result
	 * to the host. But first, cancel the timeout.
	 */
	if (cancel_delayed_work_sync(&fcopy_timeout_work)) {
		fcopy_transaction.state = HVUTIL_USERSPACE_RECV;
		fcopy_respond_to_host(*val);
		hv_poll_channel(fcopy_transaction.recv_channel,
				fcopy_poll_wrapper);
	}

	return 0;
}