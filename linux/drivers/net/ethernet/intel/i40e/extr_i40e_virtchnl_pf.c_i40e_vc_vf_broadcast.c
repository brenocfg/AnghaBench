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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct i40e_vf {int vf_id; int /*<<< orphan*/  vf_states; } ;
struct TYPE_2__ {scalar_t__ vf_base_id; } ;
struct i40e_hw {TYPE_1__ func_caps; } ;
struct i40e_pf {int num_alloc_vfs; struct i40e_vf* vf; struct i40e_hw hw; } ;
typedef  int /*<<< orphan*/  i40e_status ;
typedef  enum virtchnl_ops { ____Placeholder_virtchnl_ops } virtchnl_ops ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_VF_STATE_ACTIVE ; 
 int /*<<< orphan*/  I40E_VF_STATE_INIT ; 
 int /*<<< orphan*/  i40e_aq_send_msg_to_vf (struct i40e_hw*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i40e_vc_vf_broadcast(struct i40e_pf *pf,
				 enum virtchnl_ops v_opcode,
				 i40e_status v_retval, u8 *msg,
				 u16 msglen)
{
	struct i40e_hw *hw = &pf->hw;
	struct i40e_vf *vf = pf->vf;
	int i;

	for (i = 0; i < pf->num_alloc_vfs; i++, vf++) {
		int abs_vf_id = vf->vf_id + (int)hw->func_caps.vf_base_id;
		/* Not all vfs are enabled so skip the ones that are not */
		if (!test_bit(I40E_VF_STATE_INIT, &vf->vf_states) &&
		    !test_bit(I40E_VF_STATE_ACTIVE, &vf->vf_states))
			continue;

		/* Ignore return value on purpose - a given VF may fail, but
		 * we need to keep going and send to all of them
		 */
		i40e_aq_send_msg_to_vf(hw, abs_vf_id, v_opcode, v_retval,
				       msg, msglen, NULL);
	}
}