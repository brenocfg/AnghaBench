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
struct net_device {int dummy; } ;
struct ice_vsi {scalar_t__ type; struct ice_port_info* port_info; struct ice_pf* back; } ;
struct TYPE_5__ {int /*<<< orphan*/  req_mode; } ;
struct ice_link_status {int link_info; int an_info; } ;
struct TYPE_4__ {struct ice_link_status link_info; } ;
struct ice_port_info {TYPE_2__ fc; TYPE_1__ phy; } ;
struct TYPE_6__ {int /*<<< orphan*/  sq_last_status; } ;
struct ice_hw {TYPE_3__ adminq; } ;
struct ice_pf {int /*<<< orphan*/  state; struct ice_hw hw; } ;
struct ice_netdev_priv {struct ice_vsi* vsi; } ;
struct ethtool_pauseparam {int autoneg; scalar_t__ tx_pause; scalar_t__ rx_pause; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int ICE_AQ_AN_COMPLETED ; 
 int ICE_AQ_LINK_UP ; 
 int /*<<< orphan*/  ICE_FC_FULL ; 
 int /*<<< orphan*/  ICE_FC_NONE ; 
 int /*<<< orphan*/  ICE_FC_RX_PAUSE ; 
 int /*<<< orphan*/  ICE_FC_TX_PAUSE ; 
 int ICE_SET_FC_AQ_FAIL_GET ; 
 int ICE_SET_FC_AQ_FAIL_SET ; 
 int ICE_SET_FC_AQ_FAIL_UPDATE ; 
 scalar_t__ ICE_VSI_PF ; 
 int /*<<< orphan*/  __ICE_DOWN ; 
 int /*<<< orphan*/  ice_down (struct ice_vsi*) ; 
 int ice_nway_reset (struct net_device*) ; 
 int /*<<< orphan*/  ice_print_link_msg (struct ice_vsi*,int) ; 
 int ice_set_fc (struct ice_port_info*,int*,int) ; 
 int /*<<< orphan*/  ice_up (struct ice_vsi*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,...) ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ice_set_pauseparam(struct net_device *netdev, struct ethtool_pauseparam *pause)
{
	struct ice_netdev_priv *np = netdev_priv(netdev);
	struct ice_link_status *hw_link_info;
	struct ice_pf *pf = np->vsi->back;
	struct ice_vsi *vsi = np->vsi;
	struct ice_hw *hw = &pf->hw;
	struct ice_port_info *pi;
	enum ice_status status;
	u8 aq_failures;
	bool link_up;
	int err = 0;

	pi = vsi->port_info;
	hw_link_info = &pi->phy.link_info;
	link_up = hw_link_info->link_info & ICE_AQ_LINK_UP;

	/* Changing the port's flow control is not supported if this isn't the
	 * PF VSI
	 */
	if (vsi->type != ICE_VSI_PF) {
		netdev_info(netdev, "Changing flow control parameters only supported for PF VSI\n");
		return -EOPNOTSUPP;
	}

	if (pause->autoneg != (hw_link_info->an_info & ICE_AQ_AN_COMPLETED)) {
		netdev_info(netdev, "To change autoneg please use: ethtool -s <dev> autoneg <on|off>\n");
		return -EOPNOTSUPP;
	}

	/* If we have link and don't have autoneg */
	if (!test_bit(__ICE_DOWN, pf->state) &&
	    !(hw_link_info->an_info & ICE_AQ_AN_COMPLETED)) {
		/* Send message that it might not necessarily work*/
		netdev_info(netdev, "Autoneg did not complete so changing settings may not result in an actual change.\n");
	}

	if (pause->rx_pause && pause->tx_pause)
		pi->fc.req_mode = ICE_FC_FULL;
	else if (pause->rx_pause && !pause->tx_pause)
		pi->fc.req_mode = ICE_FC_RX_PAUSE;
	else if (!pause->rx_pause && pause->tx_pause)
		pi->fc.req_mode = ICE_FC_TX_PAUSE;
	else if (!pause->rx_pause && !pause->tx_pause)
		pi->fc.req_mode = ICE_FC_NONE;
	else
		return -EINVAL;

	/* Tell the OS link is going down, the link will go back up when fw
	 * says it is ready asynchronously
	 */
	ice_print_link_msg(vsi, false);
	netif_carrier_off(netdev);
	netif_tx_stop_all_queues(netdev);

	/* Set the FC mode and only restart AN if link is up */
	status = ice_set_fc(pi, &aq_failures, link_up);

	if (aq_failures & ICE_SET_FC_AQ_FAIL_GET) {
		netdev_info(netdev, "Set fc failed on the get_phy_capabilities call with err %d aq_err %d\n",
			    status, hw->adminq.sq_last_status);
		err = -EAGAIN;
	} else if (aq_failures & ICE_SET_FC_AQ_FAIL_SET) {
		netdev_info(netdev, "Set fc failed on the set_phy_config call with err %d aq_err %d\n",
			    status, hw->adminq.sq_last_status);
		err = -EAGAIN;
	} else if (aq_failures & ICE_SET_FC_AQ_FAIL_UPDATE) {
		netdev_info(netdev, "Set fc failed on the get_link_info call with err %d aq_err %d\n",
			    status, hw->adminq.sq_last_status);
		err = -EAGAIN;
	}

	if (!test_bit(__ICE_DOWN, pf->state)) {
		/* Give it a little more time to try to come back. If still
		 * down, restart autoneg link or reinitialize the interface.
		 */
		msleep(75);
		if (!test_bit(__ICE_DOWN, pf->state))
			return ice_nway_reset(netdev);

		ice_down(vsi);
		ice_up(vsi);
	}

	return err;
}