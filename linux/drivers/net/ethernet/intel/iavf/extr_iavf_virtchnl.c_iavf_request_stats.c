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
typedef  int /*<<< orphan*/  vqs ;
typedef  int /*<<< orphan*/  u8 ;
struct virtchnl_queue_select {int /*<<< orphan*/  vsi_id; } ;
struct iavf_adapter {scalar_t__ current_op; TYPE_1__* vsi_res; } ;
struct TYPE_2__ {int /*<<< orphan*/  vsi_id; } ;

/* Variables and functions */
 scalar_t__ VIRTCHNL_OP_GET_STATS ; 
 scalar_t__ VIRTCHNL_OP_UNKNOWN ; 
 scalar_t__ iavf_send_pf_msg (struct iavf_adapter*,scalar_t__,int /*<<< orphan*/ *,int) ; 

void iavf_request_stats(struct iavf_adapter *adapter)
{
	struct virtchnl_queue_select vqs;

	if (adapter->current_op != VIRTCHNL_OP_UNKNOWN) {
		/* no error message, this isn't crucial */
		return;
	}
	adapter->current_op = VIRTCHNL_OP_GET_STATS;
	vqs.vsi_id = adapter->vsi_res->vsi_id;
	/* queue maps are ignored for this message - only the vsi is used */
	if (iavf_send_pf_msg(adapter, VIRTCHNL_OP_GET_STATS, (u8 *)&vqs,
			     sizeof(vqs)))
		/* if the request failed, don't lock out others */
		adapter->current_op = VIRTCHNL_OP_UNKNOWN;
}