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
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct iavf_adapter {scalar_t__ current_op; int /*<<< orphan*/  aq_required; int /*<<< orphan*/  flags; TYPE_2__ ch_config; TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IAVF_FLAG_AQ_DISABLE_CHANNELS ; 
 int /*<<< orphan*/  IAVF_FLAG_REINIT_ITR_NEEDED ; 
 scalar_t__ VIRTCHNL_OP_DISABLE_CHANNELS ; 
 scalar_t__ VIRTCHNL_OP_UNKNOWN ; 
 int /*<<< orphan*/  __IAVF_TC_INVALID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  iavf_send_pf_msg (struct iavf_adapter*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void iavf_disable_channels(struct iavf_adapter *adapter)
{
	if (adapter->current_op != VIRTCHNL_OP_UNKNOWN) {
		/* bail because we already have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot configure mqprio, command %d pending\n",
			adapter->current_op);
		return;
	}

	adapter->ch_config.state = __IAVF_TC_INVALID;
	adapter->flags |= IAVF_FLAG_REINIT_ITR_NEEDED;
	adapter->current_op = VIRTCHNL_OP_DISABLE_CHANNELS;
	adapter->aq_required &= ~IAVF_FLAG_AQ_DISABLE_CHANNELS;
	iavf_send_pf_msg(adapter, VIRTCHNL_OP_DISABLE_CHANNELS, NULL, 0);
}