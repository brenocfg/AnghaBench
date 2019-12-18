#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int operation; } ;
struct hv_vss_msg {TYPE_1__ vss_hdr; } ;
struct TYPE_8__ {scalar_t__ state; TYPE_3__* msg; } ;
struct TYPE_6__ {int operation; } ;
struct TYPE_7__ {TYPE_2__ vss_hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HVUTIL_HOSTMSG_RECEIVED ; 
 scalar_t__ HVUTIL_READY ; 
 scalar_t__ HVUTIL_USERSPACE_REQ ; 
 int /*<<< orphan*/  HV_E_FAIL ; 
 int HV_UTIL_TIMEOUT ; 
 int HZ ; 
 int VSS_FREEZE_TIMEOUT ; 
 int VSS_OP_FREEZE ; 
 scalar_t__ cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hvt ; 
 int hvutil_transport_send (int /*<<< orphan*/ ,struct hv_vss_msg*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hv_vss_msg*) ; 
 struct hv_vss_msg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vss_respond_to_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vss_timeout_work ; 
 TYPE_4__ vss_transaction ; 

__attribute__((used)) static void vss_send_op(void)
{
	int op = vss_transaction.msg->vss_hdr.operation;
	int rc;
	struct hv_vss_msg *vss_msg;

	/* The transaction state is wrong. */
	if (vss_transaction.state != HVUTIL_HOSTMSG_RECEIVED) {
		pr_debug("VSS: Unexpected attempt to send to daemon\n");
		return;
	}

	vss_msg = kzalloc(sizeof(*vss_msg), GFP_KERNEL);
	if (!vss_msg)
		return;

	vss_msg->vss_hdr.operation = op;

	vss_transaction.state = HVUTIL_USERSPACE_REQ;

	schedule_delayed_work(&vss_timeout_work, op == VSS_OP_FREEZE ?
			VSS_FREEZE_TIMEOUT * HZ : HV_UTIL_TIMEOUT * HZ);

	rc = hvutil_transport_send(hvt, vss_msg, sizeof(*vss_msg), NULL);
	if (rc) {
		pr_warn("VSS: failed to communicate to the daemon: %d\n", rc);
		if (cancel_delayed_work_sync(&vss_timeout_work)) {
			vss_respond_to_host(HV_E_FAIL);
			vss_transaction.state = HVUTIL_READY;
		}
	}

	kfree(vss_msg);
}