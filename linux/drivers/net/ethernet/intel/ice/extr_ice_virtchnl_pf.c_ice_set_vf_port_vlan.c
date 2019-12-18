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
typedef  int u8 ;
typedef  int u16 ;
struct net_device {int dummy; } ;
struct TYPE_6__ {scalar_t__ pvid; } ;
struct ice_vsi {TYPE_3__ info; } ;
struct ice_vf {size_t lan_vsi_idx; int port_vlan_id; int /*<<< orphan*/  vf_states; } ;
struct ice_pf {int num_alloc_vfs; TYPE_2__* pdev; struct ice_vsi** vsi; struct ice_vf* vf; } ;
struct ice_netdev_priv {TYPE_1__* vsi; } ;
typedef  scalar_t__ __be16 ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct ice_pf* back; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int ICE_MAX_VLANID ; 
 int /*<<< orphan*/  ICE_VF_STATE_INIT ; 
 int ICE_VLAN_PRIORITY_S ; 
 int VLAN_VID_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,...) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int ice_vsi_add_vlan (struct ice_vsi*,int) ; 
 int /*<<< orphan*/  ice_vsi_kill_vlan (struct ice_vsi*,int) ; 
 int ice_vsi_manage_pvid (struct ice_vsi*,int,int) ; 
 int le16_to_cpu (scalar_t__) ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ice_set_vf_port_vlan(struct net_device *netdev, int vf_id, u16 vlan_id, u8 qos,
		     __be16 vlan_proto)
{
	u16 vlanprio = vlan_id | (qos << ICE_VLAN_PRIORITY_S);
	struct ice_netdev_priv *np = netdev_priv(netdev);
	struct ice_pf *pf = np->vsi->back;
	struct ice_vsi *vsi;
	struct ice_vf *vf;
	int ret = 0;

	/* validate the request */
	if (vf_id >= pf->num_alloc_vfs) {
		dev_err(&pf->pdev->dev, "invalid VF id: %d\n", vf_id);
		return -EINVAL;
	}

	if (vlan_id > ICE_MAX_VLANID || qos > 7) {
		dev_err(&pf->pdev->dev, "Invalid VF Parameters\n");
		return -EINVAL;
	}

	if (vlan_proto != htons(ETH_P_8021Q)) {
		dev_err(&pf->pdev->dev, "VF VLAN protocol is not supported\n");
		return -EPROTONOSUPPORT;
	}

	vf = &pf->vf[vf_id];
	vsi = pf->vsi[vf->lan_vsi_idx];
	if (!test_bit(ICE_VF_STATE_INIT, vf->vf_states)) {
		dev_err(&pf->pdev->dev, "VF %d in reset. Try again.\n", vf_id);
		return -EBUSY;
	}

	if (le16_to_cpu(vsi->info.pvid) == vlanprio) {
		/* duplicate request, so just return success */
		dev_info(&pf->pdev->dev,
			 "Duplicate pvid %d request\n", vlanprio);
		return ret;
	}

	/* If PVID, then remove all filters on the old VLAN */
	if (vsi->info.pvid)
		ice_vsi_kill_vlan(vsi, (le16_to_cpu(vsi->info.pvid) &
				  VLAN_VID_MASK));

	if (vlan_id || qos) {
		ret = ice_vsi_manage_pvid(vsi, vlanprio, true);
		if (ret)
			goto error_set_pvid;
	} else {
		ice_vsi_manage_pvid(vsi, 0, false);
		vsi->info.pvid = 0;
	}

	if (vlan_id) {
		dev_info(&pf->pdev->dev, "Setting VLAN %d, QOS 0x%x on VF %d\n",
			 vlan_id, qos, vf_id);

		/* add new VLAN filter for each MAC */
		ret = ice_vsi_add_vlan(vsi, vlan_id);
		if (ret)
			goto error_set_pvid;
	}

	/* The Port VLAN needs to be saved across resets the same as the
	 * default LAN MAC address.
	 */
	vf->port_vlan_id = le16_to_cpu(vsi->info.pvid);

error_set_pvid:
	return ret;
}