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
struct net_device {int dummy; } ;
struct i40e_vsi {int /*<<< orphan*/  seid; } ;
struct i40e_vf {size_t lan_vsi_idx; int tx_rate; int /*<<< orphan*/  vf_states; } ;
struct i40e_pf {int /*<<< orphan*/  state; TYPE_2__* pdev; struct i40e_vsi** vsi; struct i40e_vf* vf; } ;
struct i40e_netdev_priv {TYPE_1__* vsi; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct i40e_pf* back; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  I40E_VF_STATE_INIT ; 
 int /*<<< orphan*/  __I40E_VIRTCHNL_OP_PENDING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int i40e_set_bw_limit (struct i40e_vsi*,int /*<<< orphan*/ ,int) ; 
 int i40e_validate_vf (struct i40e_pf*,int) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int i40e_ndo_set_vf_bw(struct net_device *netdev, int vf_id, int min_tx_rate,
		       int max_tx_rate)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_pf *pf = np->vsi->back;
	struct i40e_vsi *vsi;
	struct i40e_vf *vf;
	int ret = 0;

	if (test_and_set_bit(__I40E_VIRTCHNL_OP_PENDING, pf->state)) {
		dev_warn(&pf->pdev->dev, "Unable to configure VFs, other operation is pending.\n");
		return -EAGAIN;
	}

	/* validate the request */
	ret = i40e_validate_vf(pf, vf_id);
	if (ret)
		goto error;

	if (min_tx_rate) {
		dev_err(&pf->pdev->dev, "Invalid min tx rate (%d) (greater than 0) specified for VF %d.\n",
			min_tx_rate, vf_id);
		ret = -EINVAL;
		goto error;
	}

	vf = &pf->vf[vf_id];
	vsi = pf->vsi[vf->lan_vsi_idx];
	if (!test_bit(I40E_VF_STATE_INIT, &vf->vf_states)) {
		dev_err(&pf->pdev->dev, "VF %d still in reset. Try again.\n",
			vf_id);
		ret = -EAGAIN;
		goto error;
	}

	ret = i40e_set_bw_limit(vsi, vsi->seid, max_tx_rate);
	if (ret)
		goto error;

	vf->tx_rate = max_tx_rate;
error:
	clear_bit(__I40E_VIRTCHNL_OP_PENDING, pf->state);
	return ret;
}