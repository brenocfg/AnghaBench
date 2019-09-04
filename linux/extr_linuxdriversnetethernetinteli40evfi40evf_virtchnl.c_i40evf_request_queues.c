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
typedef  int /*<<< orphan*/  vfres ;
typedef  int /*<<< orphan*/  u8 ;
struct virtchnl_vf_res_request {int num_queue_pairs; } ;
struct i40evf_adapter {scalar_t__ current_op; int /*<<< orphan*/  flags; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  I40EVF_FLAG_REINIT_ITR_NEEDED ; 
 scalar_t__ VIRTCHNL_OP_REQUEST_QUEUES ; 
 scalar_t__ VIRTCHNL_OP_UNKNOWN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int i40evf_send_pf_msg (struct i40evf_adapter*,scalar_t__,int /*<<< orphan*/ *,int) ; 

int i40evf_request_queues(struct i40evf_adapter *adapter, int num)
{
	struct virtchnl_vf_res_request vfres;

	if (adapter->current_op != VIRTCHNL_OP_UNKNOWN) {
		/* bail because we already have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot request queues, command %d pending\n",
			adapter->current_op);
		return -EBUSY;
	}

	vfres.num_queue_pairs = num;

	adapter->current_op = VIRTCHNL_OP_REQUEST_QUEUES;
	adapter->flags |= I40EVF_FLAG_REINIT_ITR_NEEDED;
	return i40evf_send_pf_msg(adapter, VIRTCHNL_OP_REQUEST_QUEUES,
				  (u8 *)&vfres, sizeof(vfres));
}