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
struct TYPE_7__ {int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;
struct viosrp_fast_fail {TYPE_3__ common; } ;
struct TYPE_5__ {struct viosrp_fast_fail fast_fail; } ;
struct TYPE_6__ {TYPE_1__ mad; } ;
struct srp_event_struct {TYPE_2__ iu; } ;
struct ibmvscsi_host_data {TYPE_4__* host; int /*<<< orphan*/  pool; } ;
struct TYPE_8__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  VIOSRP_ENABLE_FAST_FAIL ; 
 int /*<<< orphan*/  VIOSRP_MAD_FORMAT ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fast_fail ; 
 int /*<<< orphan*/  fast_fail_rsp ; 
 struct srp_event_struct* get_event_struct (int /*<<< orphan*/ *) ; 
 int ibmvscsi_send_srp_event (struct srp_event_struct*,struct ibmvscsi_host_data*,int) ; 
 int info_timeout ; 
 int /*<<< orphan*/  init_event_struct (struct srp_event_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct viosrp_fast_fail*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  send_mad_capabilities (struct ibmvscsi_host_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int enable_fast_fail(struct ibmvscsi_host_data *hostdata)
{
	int rc;
	unsigned long flags;
	struct viosrp_fast_fail *fast_fail_mad;
	struct srp_event_struct *evt_struct;

	if (!fast_fail) {
		send_mad_capabilities(hostdata);
		return 0;
	}

	evt_struct = get_event_struct(&hostdata->pool);
	BUG_ON(!evt_struct);

	init_event_struct(evt_struct, fast_fail_rsp, VIOSRP_MAD_FORMAT, info_timeout);

	fast_fail_mad = &evt_struct->iu.mad.fast_fail;
	memset(fast_fail_mad, 0, sizeof(*fast_fail_mad));
	fast_fail_mad->common.type = cpu_to_be32(VIOSRP_ENABLE_FAST_FAIL);
	fast_fail_mad->common.length = cpu_to_be16(sizeof(*fast_fail_mad));

	spin_lock_irqsave(hostdata->host->host_lock, flags);
	rc = ibmvscsi_send_srp_event(evt_struct, hostdata, info_timeout * 2);
	spin_unlock_irqrestore(hostdata->host->host_lock, flags);
	return rc;
}