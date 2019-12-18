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
 int /*<<< orphan*/  CN_VSS_IDX ; 
 int /*<<< orphan*/  CN_VSS_VAL ; 
 int EFAULT ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  HVUTIL_DEVICE_INIT ; 
 scalar_t__ VERSION_WIN8_1 ; 
 int /*<<< orphan*/  hvt ; 
 int /*<<< orphan*/  hvutil_transport_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  recv_buffer ; 
 scalar_t__ vmbus_proto_version ; 
 int /*<<< orphan*/  vss_devname ; 
 int /*<<< orphan*/  vss_on_msg ; 
 int /*<<< orphan*/  vss_on_reset ; 
 TYPE_1__ vss_transaction ; 

int
hv_vss_init(struct hv_util_service *srv)
{
	if (vmbus_proto_version < VERSION_WIN8_1) {
		pr_warn("Integration service 'Backup (volume snapshot)'"
			" not supported on this host version.\n");
		return -ENOTSUPP;
	}
	recv_buffer = srv->recv_buffer;
	vss_transaction.recv_channel = srv->channel;

	/*
	 * When this driver loads, the user level daemon that
	 * processes the host requests may not yet be running.
	 * Defer processing channel callbacks until the daemon
	 * has registered.
	 */
	vss_transaction.state = HVUTIL_DEVICE_INIT;

	hvt = hvutil_transport_init(vss_devname, CN_VSS_IDX, CN_VSS_VAL,
				    vss_on_msg, vss_on_reset);
	if (!hvt) {
		pr_warn("VSS: Failed to initialize transport\n");
		return -EFAULT;
	}

	return 0;
}