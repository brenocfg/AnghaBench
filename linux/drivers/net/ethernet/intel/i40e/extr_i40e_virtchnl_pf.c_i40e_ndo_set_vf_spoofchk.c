#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_5__ {int sec_flags; int /*<<< orphan*/  valid_sections; } ;
struct i40e_vsi_context {TYPE_2__ info; int /*<<< orphan*/  pf_num; int /*<<< orphan*/  seid; } ;
struct i40e_vsi {struct i40e_pf* back; } ;
struct i40e_vf {int spoofchk; size_t lan_vsi_idx; int /*<<< orphan*/  vf_states; } ;
struct i40e_hw {int /*<<< orphan*/  pf_id; } ;
struct i40e_pf {int num_alloc_vfs; int /*<<< orphan*/  state; TYPE_3__* pdev; struct i40e_hw hw; TYPE_1__** vsi; struct i40e_vf* vf; } ;
struct i40e_netdev_priv {struct i40e_vsi* vsi; } ;
typedef  int /*<<< orphan*/  ctxt ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  seid; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  I40E_AQ_VSI_PROP_SECURITY_VALID ; 
 int I40E_AQ_VSI_SEC_FLAG_ENABLE_MAC_CHK ; 
 int I40E_AQ_VSI_SEC_FLAG_ENABLE_VLAN_CHK ; 
 int /*<<< orphan*/  I40E_VF_STATE_INIT ; 
 int /*<<< orphan*/  __I40E_VIRTCHNL_OP_PENDING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int i40e_aq_update_vsi_params (struct i40e_hw*,struct i40e_vsi_context*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct i40e_vsi_context*,int /*<<< orphan*/ ,int) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int i40e_ndo_set_vf_spoofchk(struct net_device *netdev, int vf_id, bool enable)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_vsi *vsi = np->vsi;
	struct i40e_pf *pf = vsi->back;
	struct i40e_vsi_context ctxt;
	struct i40e_hw *hw = &pf->hw;
	struct i40e_vf *vf;
	int ret = 0;

	if (test_and_set_bit(__I40E_VIRTCHNL_OP_PENDING, pf->state)) {
		dev_warn(&pf->pdev->dev, "Unable to configure VFs, other operation is pending.\n");
		return -EAGAIN;
	}

	/* validate the request */
	if (vf_id >= pf->num_alloc_vfs) {
		dev_err(&pf->pdev->dev, "Invalid VF Identifier %d\n", vf_id);
		ret = -EINVAL;
		goto out;
	}

	vf = &(pf->vf[vf_id]);
	if (!test_bit(I40E_VF_STATE_INIT, &vf->vf_states)) {
		dev_err(&pf->pdev->dev, "VF %d still in reset. Try again.\n",
			vf_id);
		ret = -EAGAIN;
		goto out;
	}

	if (enable == vf->spoofchk)
		goto out;

	vf->spoofchk = enable;
	memset(&ctxt, 0, sizeof(ctxt));
	ctxt.seid = pf->vsi[vf->lan_vsi_idx]->seid;
	ctxt.pf_num = pf->hw.pf_id;
	ctxt.info.valid_sections = cpu_to_le16(I40E_AQ_VSI_PROP_SECURITY_VALID);
	if (enable)
		ctxt.info.sec_flags |= (I40E_AQ_VSI_SEC_FLAG_ENABLE_VLAN_CHK |
					I40E_AQ_VSI_SEC_FLAG_ENABLE_MAC_CHK);
	ret = i40e_aq_update_vsi_params(hw, &ctxt, NULL);
	if (ret) {
		dev_err(&pf->pdev->dev, "Error %d updating VSI parameters\n",
			ret);
		ret = -EIO;
	}
out:
	clear_bit(__I40E_VIRTCHNL_OP_PENDING, pf->state);
	return ret;
}