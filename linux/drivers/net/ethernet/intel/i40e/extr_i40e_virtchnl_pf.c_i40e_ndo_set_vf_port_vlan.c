#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct net_device {int dummy; } ;
struct TYPE_12__ {scalar_t__ pvid; } ;
struct i40e_vsi {int /*<<< orphan*/  id; TYPE_5__ info; TYPE_7__* back; int /*<<< orphan*/  mac_filter_hash_lock; } ;
struct i40e_vf {size_t lan_vsi_idx; int port_vlan_id; int /*<<< orphan*/  vf_states; int /*<<< orphan*/  lan_vsi_id; } ;
struct i40e_pf {int /*<<< orphan*/  state; TYPE_6__* pdev; struct i40e_vsi** vsi; struct i40e_vf* vf; } ;
struct i40e_netdev_priv {TYPE_1__* vsi; } ;
typedef  scalar_t__ __be16 ;
struct TYPE_10__ {int /*<<< orphan*/  asq_last_status; } ;
struct TYPE_11__ {TYPE_3__ aq; } ;
struct TYPE_14__ {TYPE_4__ hw; TYPE_2__* pdev; } ;
struct TYPE_13__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {struct i40e_pf* back; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int I40E_MAX_VLANID ; 
 int /*<<< orphan*/  I40E_VF_STATE_INIT ; 
 int /*<<< orphan*/  I40E_VF_STATE_MC_PROMISC ; 
 int /*<<< orphan*/  I40E_VF_STATE_UC_PROMISC ; 
 int I40E_VLAN_ANY ; 
 int I40E_VLAN_PRIORITY_SHIFT ; 
 int VLAN_VID_MASK ; 
 int /*<<< orphan*/  __I40E_VIRTCHNL_OP_PENDING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int i40e_add_vlan_all_mac (struct i40e_vsi*,int) ; 
 int i40e_config_vf_promiscuous_mode (struct i40e_vf*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  i40e_rm_vlan_all_mac (struct i40e_vsi*,int) ; 
 int /*<<< orphan*/  i40e_service_event_schedule (TYPE_7__*) ; 
 int i40e_validate_vf (struct i40e_pf*,int) ; 
 int /*<<< orphan*/  i40e_vc_disable_vf (struct i40e_vf*) ; 
 int i40e_vsi_add_pvid (struct i40e_vsi*,int) ; 
 scalar_t__ i40e_vsi_has_vlans (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_vsi_remove_pvid (struct i40e_vsi*) ; 
 int le16_to_cpu (scalar_t__) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int i40e_ndo_set_vf_port_vlan(struct net_device *netdev, int vf_id,
			      u16 vlan_id, u8 qos, __be16 vlan_proto)
{
	u16 vlanprio = vlan_id | (qos << I40E_VLAN_PRIORITY_SHIFT);
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	bool allmulti = false, alluni = false;
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
		goto error_pvid;

	if ((vlan_id > I40E_MAX_VLANID) || (qos > 7)) {
		dev_err(&pf->pdev->dev, "Invalid VF Parameters\n");
		ret = -EINVAL;
		goto error_pvid;
	}

	if (vlan_proto != htons(ETH_P_8021Q)) {
		dev_err(&pf->pdev->dev, "VF VLAN protocol is not supported\n");
		ret = -EPROTONOSUPPORT;
		goto error_pvid;
	}

	vf = &pf->vf[vf_id];
	vsi = pf->vsi[vf->lan_vsi_idx];
	if (!test_bit(I40E_VF_STATE_INIT, &vf->vf_states)) {
		dev_err(&pf->pdev->dev, "VF %d still in reset. Try again.\n",
			vf_id);
		ret = -EAGAIN;
		goto error_pvid;
	}

	if (le16_to_cpu(vsi->info.pvid) == vlanprio)
		/* duplicate request, so just return success */
		goto error_pvid;

	if (i40e_vsi_has_vlans(vsi)) {
		dev_err(&pf->pdev->dev,
			"VF %d has already configured VLAN filters and the administrator is requesting a port VLAN override.\nPlease unload and reload the VF driver for this change to take effect.\n",
			vf_id);
		/* Administrator Error - knock the VF offline until he does
		 * the right thing by reconfiguring his network correctly
		 * and then reloading the VF driver.
		 */
		i40e_vc_disable_vf(vf);
		/* During reset the VF got a new VSI, so refresh the pointer. */
		vsi = pf->vsi[vf->lan_vsi_idx];
	}

	/* Locked once because multiple functions below iterate list */
	spin_lock_bh(&vsi->mac_filter_hash_lock);

	/* Check for condition where there was already a port VLAN ID
	 * filter set and now it is being deleted by setting it to zero.
	 * Additionally check for the condition where there was a port
	 * VLAN but now there is a new and different port VLAN being set.
	 * Before deleting all the old VLAN filters we must add new ones
	 * with -1 (I40E_VLAN_ANY) or otherwise we're left with all our
	 * MAC addresses deleted.
	 */
	if ((!(vlan_id || qos) ||
	    vlanprio != le16_to_cpu(vsi->info.pvid)) &&
	    vsi->info.pvid) {
		ret = i40e_add_vlan_all_mac(vsi, I40E_VLAN_ANY);
		if (ret) {
			dev_info(&vsi->back->pdev->dev,
				 "add VF VLAN failed, ret=%d aq_err=%d\n", ret,
				 vsi->back->hw.aq.asq_last_status);
			spin_unlock_bh(&vsi->mac_filter_hash_lock);
			goto error_pvid;
		}
	}

	if (vsi->info.pvid) {
		/* remove all filters on the old VLAN */
		i40e_rm_vlan_all_mac(vsi, (le16_to_cpu(vsi->info.pvid) &
					   VLAN_VID_MASK));
	}

	spin_unlock_bh(&vsi->mac_filter_hash_lock);

	/* disable promisc modes in case they were enabled */
	ret = i40e_config_vf_promiscuous_mode(vf, vf->lan_vsi_id,
					      allmulti, alluni);
	if (ret) {
		dev_err(&pf->pdev->dev, "Unable to config VF promiscuous mode\n");
		goto error_pvid;
	}

	if (vlan_id || qos)
		ret = i40e_vsi_add_pvid(vsi, vlanprio);
	else
		i40e_vsi_remove_pvid(vsi);
	spin_lock_bh(&vsi->mac_filter_hash_lock);

	if (vlan_id) {
		dev_info(&pf->pdev->dev, "Setting VLAN %d, QOS 0x%x on VF %d\n",
			 vlan_id, qos, vf_id);

		/* add new VLAN filter for each MAC */
		ret = i40e_add_vlan_all_mac(vsi, vlan_id);
		if (ret) {
			dev_info(&vsi->back->pdev->dev,
				 "add VF VLAN failed, ret=%d aq_err=%d\n", ret,
				 vsi->back->hw.aq.asq_last_status);
			spin_unlock_bh(&vsi->mac_filter_hash_lock);
			goto error_pvid;
		}

		/* remove the previously added non-VLAN MAC filters */
		i40e_rm_vlan_all_mac(vsi, I40E_VLAN_ANY);
	}

	spin_unlock_bh(&vsi->mac_filter_hash_lock);

	if (test_bit(I40E_VF_STATE_UC_PROMISC, &vf->vf_states))
		alluni = true;

	if (test_bit(I40E_VF_STATE_MC_PROMISC, &vf->vf_states))
		allmulti = true;

	/* Schedule the worker thread to take care of applying changes */
	i40e_service_event_schedule(vsi->back);

	if (ret) {
		dev_err(&pf->pdev->dev, "Unable to update VF vsi context\n");
		goto error_pvid;
	}

	/* The Port VLAN needs to be saved across resets the same as the
	 * default LAN MAC address.
	 */
	vf->port_vlan_id = le16_to_cpu(vsi->info.pvid);

	ret = i40e_config_vf_promiscuous_mode(vf, vsi->id, allmulti, alluni);
	if (ret) {
		dev_err(&pf->pdev->dev, "Unable to config vf promiscuous mode\n");
		goto error_pvid;
	}

	ret = 0;

error_pvid:
	clear_bit(__I40E_VIRTCHNL_OP_PENDING, pf->state);
	return ret;
}