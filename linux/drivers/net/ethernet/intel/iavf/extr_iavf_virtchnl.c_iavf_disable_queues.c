#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vqs ;
typedef  int /*<<< orphan*/  u8 ;
struct virtchnl_queue_select {scalar_t__ tx_queues; scalar_t__ rx_queues; int /*<<< orphan*/  vsi_id; } ;
struct iavf_adapter {scalar_t__ current_op; int /*<<< orphan*/  aq_required; int /*<<< orphan*/  num_active_queues; TYPE_1__* vsi_res; TYPE_2__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  vsi_id; } ;

/* Variables and functions */
 scalar_t__ BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IAVF_FLAG_AQ_DISABLE_QUEUES ; 
 scalar_t__ VIRTCHNL_OP_DISABLE_QUEUES ; 
 scalar_t__ VIRTCHNL_OP_UNKNOWN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  iavf_send_pf_msg (struct iavf_adapter*,scalar_t__,int /*<<< orphan*/ *,int) ; 

void iavf_disable_queues(struct iavf_adapter *adapter)
{
	struct virtchnl_queue_select vqs;

	if (adapter->current_op != VIRTCHNL_OP_UNKNOWN) {
		/* bail because we already have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot disable queues, command %d pending\n",
			adapter->current_op);
		return;
	}
	adapter->current_op = VIRTCHNL_OP_DISABLE_QUEUES;
	vqs.vsi_id = adapter->vsi_res->vsi_id;
	vqs.tx_queues = BIT(adapter->num_active_queues) - 1;
	vqs.rx_queues = vqs.tx_queues;
	adapter->aq_required &= ~IAVF_FLAG_AQ_DISABLE_QUEUES;
	iavf_send_pf_msg(adapter, VIRTCHNL_OP_DISABLE_QUEUES,
			 (u8 *)&vqs, sizeof(vqs));
}