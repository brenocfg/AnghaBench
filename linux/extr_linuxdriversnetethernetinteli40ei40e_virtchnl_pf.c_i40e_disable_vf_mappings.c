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
struct i40e_vf {int /*<<< orphan*/  vf_id; struct i40e_pf* pf; } ;
struct i40e_hw {int dummy; } ;
struct i40e_pf {struct i40e_hw hw; } ;

/* Variables and functions */
 int I40E_MAX_VSI_QP ; 
 int /*<<< orphan*/  I40E_QUEUE_END_OF_LIST ; 
 int /*<<< orphan*/  I40E_VPLAN_MAPENA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_VPLAN_QTABLE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_flush (struct i40e_hw*) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_disable_vf_mappings(struct i40e_vf *vf)
{
	struct i40e_pf *pf = vf->pf;
	struct i40e_hw *hw = &pf->hw;
	int i;

	/* disable qp mappings */
	wr32(hw, I40E_VPLAN_MAPENA(vf->vf_id), 0);
	for (i = 0; i < I40E_MAX_VSI_QP; i++)
		wr32(hw, I40E_VPLAN_QTABLE(i, vf->vf_id),
		     I40E_QUEUE_END_OF_LIST);
	i40e_flush(hw);
}