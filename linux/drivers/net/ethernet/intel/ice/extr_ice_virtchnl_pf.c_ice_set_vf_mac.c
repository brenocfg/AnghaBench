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
struct net_device {int dummy; } ;
struct ice_vsi {struct ice_pf* back; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct ice_vf {int pf_set_mac; TYPE_1__ dflt_lan_addr; int /*<<< orphan*/  vf_states; } ;
struct ice_pf {int num_alloc_vfs; struct ice_vf* vf; } ;
struct ice_netdev_priv {struct ice_vsi* vsi; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  ICE_VF_STATE_INIT ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_vc_dis_vf (struct ice_vf*) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ *) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int,int /*<<< orphan*/ *) ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ice_set_vf_mac(struct net_device *netdev, int vf_id, u8 *mac)
{
	struct ice_netdev_priv *np = netdev_priv(netdev);
	struct ice_vsi *vsi = np->vsi;
	struct ice_pf *pf = vsi->back;
	struct ice_vf *vf;
	int ret = 0;

	/* validate the request */
	if (vf_id >= pf->num_alloc_vfs) {
		netdev_err(netdev, "invalid VF id: %d\n", vf_id);
		return -EINVAL;
	}

	vf = &pf->vf[vf_id];
	if (!test_bit(ICE_VF_STATE_INIT, vf->vf_states)) {
		netdev_err(netdev, "VF %d in reset. Try again.\n", vf_id);
		return -EBUSY;
	}

	if (is_zero_ether_addr(mac) || is_multicast_ether_addr(mac)) {
		netdev_err(netdev, "%pM not a valid unicast address\n", mac);
		return -EINVAL;
	}

	/* copy MAC into dflt_lan_addr and trigger a VF reset. The reset
	 * flow will use the updated dflt_lan_addr and add a MAC filter
	 * using ice_add_mac. Also set pf_set_mac to indicate that the PF has
	 * set the MAC address for this VF.
	 */
	ether_addr_copy(vf->dflt_lan_addr.addr, mac);
	vf->pf_set_mac = true;
	netdev_info(netdev,
		    "MAC on VF %d set to %pM. VF driver will be reinitialized\n",
		    vf_id, mac);

	ice_vc_dis_vf(vf);
	return ret;
}