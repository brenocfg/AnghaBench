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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  asq_last_status; } ;
struct i40e_hw {TYPE_1__ aq; } ;
struct i40evf_adapter {int flags; TYPE_2__* pdev; struct i40e_hw hw; } ;
typedef  int i40e_status ;
typedef  enum virtchnl_ops { ____Placeholder_virtchnl_ops } virtchnl_ops ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int I40EVF_FLAG_PF_COMMS_FAILED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i40e_aq_send_msg_to_pf (struct i40e_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40evf_aq_str (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40evf_stat_str (struct i40e_hw*,int) ; 

__attribute__((used)) static int i40evf_send_pf_msg(struct i40evf_adapter *adapter,
			      enum virtchnl_ops op, u8 *msg, u16 len)
{
	struct i40e_hw *hw = &adapter->hw;
	i40e_status err;

	if (adapter->flags & I40EVF_FLAG_PF_COMMS_FAILED)
		return 0; /* nothing to see here, move along */

	err = i40e_aq_send_msg_to_pf(hw, op, 0, msg, len, NULL);
	if (err)
		dev_dbg(&adapter->pdev->dev, "Unable to send opcode %d to PF, err %s, aq_err %s\n",
			op, i40evf_stat_str(hw, err),
			i40evf_aq_str(hw, hw->aq.asq_last_status));
	return err;
}