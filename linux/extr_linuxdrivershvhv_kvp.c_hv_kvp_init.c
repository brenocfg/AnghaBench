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
 int /*<<< orphan*/  CN_KVP_IDX ; 
 int /*<<< orphan*/  CN_KVP_VAL ; 
 int EFAULT ; 
 int /*<<< orphan*/  HVUTIL_DEVICE_INIT ; 
 int /*<<< orphan*/  hvt ; 
 int /*<<< orphan*/  hvutil_transport_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvp_devname ; 
 int /*<<< orphan*/  kvp_on_msg ; 
 int /*<<< orphan*/  kvp_on_reset ; 
 TYPE_1__ kvp_transaction ; 
 int /*<<< orphan*/  recv_buffer ; 

int
hv_kvp_init(struct hv_util_service *srv)
{
	recv_buffer = srv->recv_buffer;
	kvp_transaction.recv_channel = srv->channel;

	/*
	 * When this driver loads, the user level daemon that
	 * processes the host requests may not yet be running.
	 * Defer processing channel callbacks until the daemon
	 * has registered.
	 */
	kvp_transaction.state = HVUTIL_DEVICE_INIT;

	hvt = hvutil_transport_init(kvp_devname, CN_KVP_IDX, CN_KVP_VAL,
				    kvp_on_msg, kvp_on_reset);
	if (!hvt)
		return -EFAULT;

	return 0;
}