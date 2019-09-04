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
struct i40e_hw {int dummy; } ;
typedef  int /*<<< orphan*/  i40e_status ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTCHNL_OP_RESET_VF ; 
 int /*<<< orphan*/  i40e_aq_send_msg_to_pf (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

i40e_status i40e_vf_reset(struct i40e_hw *hw)
{
	return i40e_aq_send_msg_to_pf(hw, VIRTCHNL_OP_RESET_VF,
				      0, NULL, 0, NULL);
}