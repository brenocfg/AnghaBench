#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct iavf_adapter {int /*<<< orphan*/  current_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTCHNL_OP_RESET_VF ; 
 int /*<<< orphan*/  VIRTCHNL_OP_UNKNOWN ; 
 int /*<<< orphan*/  iavf_send_pf_msg (struct iavf_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void iavf_request_reset(struct iavf_adapter *adapter)
{
	/* Don't check CURRENT_OP - this is always higher priority */
	iavf_send_pf_msg(adapter, VIRTCHNL_OP_RESET_VF, NULL, 0);
	adapter->current_op = VIRTCHNL_OP_UNKNOWN;
}