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
struct i40e_vsi {scalar_t__ type; int /*<<< orphan*/  seid; } ;
struct TYPE_4__ {int /*<<< orphan*/  asq_last_status; } ;
struct i40e_hw {TYPE_2__ aq; } ;
struct i40e_pf {size_t lan_vsi; scalar_t__ lan_veb; int flags; int cur_promisc; TYPE_1__* pdev; struct i40e_hw hw; struct i40e_vsi** vsi; } ;
typedef  int i40e_status ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int I40E_FLAG_MFP_ENABLED ; 
 scalar_t__ I40E_NO_VEB ; 
 scalar_t__ I40E_VSI_MAIN ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i40e_aq_clear_default_vsi (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int i40e_aq_set_default_vsi (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int i40e_aq_set_vsi_multicast_promiscuous (struct i40e_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int i40e_aq_set_vsi_unicast_promiscuous (struct i40e_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i40e_aq_str (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_stat_str (struct i40e_hw*,int) ; 

__attribute__((used)) static int i40e_set_promiscuous(struct i40e_pf *pf, bool promisc)
{
	struct i40e_vsi *vsi = pf->vsi[pf->lan_vsi];
	struct i40e_hw *hw = &pf->hw;
	i40e_status aq_ret;

	if (vsi->type == I40E_VSI_MAIN &&
	    pf->lan_veb != I40E_NO_VEB &&
	    !(pf->flags & I40E_FLAG_MFP_ENABLED)) {
		/* set defport ON for Main VSI instead of true promisc
		 * this way we will get all unicast/multicast and VLAN
		 * promisc behavior but will not get VF or VMDq traffic
		 * replicated on the Main VSI.
		 */
		if (promisc)
			aq_ret = i40e_aq_set_default_vsi(hw,
							 vsi->seid,
							 NULL);
		else
			aq_ret = i40e_aq_clear_default_vsi(hw,
							   vsi->seid,
							   NULL);
		if (aq_ret) {
			dev_info(&pf->pdev->dev,
				 "Set default VSI failed, err %s, aq_err %s\n",
				 i40e_stat_str(hw, aq_ret),
				 i40e_aq_str(hw, hw->aq.asq_last_status));
		}
	} else {
		aq_ret = i40e_aq_set_vsi_unicast_promiscuous(
						  hw,
						  vsi->seid,
						  promisc, NULL,
						  true);
		if (aq_ret) {
			dev_info(&pf->pdev->dev,
				 "set unicast promisc failed, err %s, aq_err %s\n",
				 i40e_stat_str(hw, aq_ret),
				 i40e_aq_str(hw, hw->aq.asq_last_status));
		}
		aq_ret = i40e_aq_set_vsi_multicast_promiscuous(
						  hw,
						  vsi->seid,
						  promisc, NULL);
		if (aq_ret) {
			dev_info(&pf->pdev->dev,
				 "set multicast promisc failed, err %s, aq_err %s\n",
				 i40e_stat_str(hw, aq_ret),
				 i40e_aq_str(hw, hw->aq.asq_last_status));
		}
	}

	if (!aq_ret)
		pf->cur_promisc = promisc;

	return aq_ret;
}