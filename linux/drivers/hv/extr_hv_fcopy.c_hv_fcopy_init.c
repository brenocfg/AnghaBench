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
struct hv_util_service {int /*<<< orphan*/  channel; int /*<<< orphan*/  recv_buffer; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; int /*<<< orphan*/  recv_channel; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  HVUTIL_DEVICE_INIT ; 
 int /*<<< orphan*/  fcopy_devname ; 
 int /*<<< orphan*/  fcopy_on_msg ; 
 int /*<<< orphan*/  fcopy_on_reset ; 
 TYPE_1__ fcopy_transaction ; 
 int /*<<< orphan*/  hvt ; 
 int /*<<< orphan*/  hvutil_transport_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recv_buffer ; 

int hv_fcopy_init(struct hv_util_service *srv)
{
	recv_buffer = srv->recv_buffer;
	fcopy_transaction.recv_channel = srv->channel;

	/*
	 * When this driver loads, the user level daemon that
	 * processes the host requests may not yet be running.
	 * Defer processing channel callbacks until the daemon
	 * has registered.
	 */
	fcopy_transaction.state = HVUTIL_DEVICE_INIT;

	hvt = hvutil_transport_init(fcopy_devname, 0, 0,
				    fcopy_on_msg, fcopy_on_reset);
	if (!hvt)
		return -EFAULT;

	return 0;
}