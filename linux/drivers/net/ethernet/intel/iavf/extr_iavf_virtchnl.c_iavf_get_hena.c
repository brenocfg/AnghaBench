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
struct iavf_adapter {scalar_t__ current_op; int /*<<< orphan*/  aq_required; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IAVF_FLAG_AQ_GET_HENA ; 
 scalar_t__ VIRTCHNL_OP_GET_RSS_HENA_CAPS ; 
 scalar_t__ VIRTCHNL_OP_UNKNOWN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  iavf_send_pf_msg (struct iavf_adapter*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void iavf_get_hena(struct iavf_adapter *adapter)
{
	if (adapter->current_op != VIRTCHNL_OP_UNKNOWN) {
		/* bail because we already have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot get RSS hash capabilities, command %d pending\n",
			adapter->current_op);
		return;
	}
	adapter->current_op = VIRTCHNL_OP_GET_RSS_HENA_CAPS;
	adapter->aq_required &= ~IAVF_FLAG_AQ_GET_HENA;
	iavf_send_pf_msg(adapter, VIRTCHNL_OP_GET_RSS_HENA_CAPS, NULL, 0);
}