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
typedef  size_t u32 ;
struct net_device {int dummy; } ;
struct ice_vsi {struct ice_pf* back; } ;
struct ice_priv_flag {int /*<<< orphan*/  bitno; } ;
struct ice_pf {int /*<<< orphan*/  flags; TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct ice_netdev_priv {struct ice_vsi* vsi; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t BIT (size_t) ; 
 int /*<<< orphan*/  DECLARE_BITMAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ICE_FLAG_ETHTOOL_CTXT ; 
 int /*<<< orphan*/  ICE_FLAG_FW_LLDP_AGENT ; 
 int /*<<< orphan*/  ICE_PF_FLAGS_NBITS ; 
 size_t ICE_PRIV_FLAG_ARRAY_SIZE ; 
 int /*<<< orphan*/  bitmap_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_xor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  change_flags ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int ice_aq_start_lldp (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int ice_aq_start_stop_dcbx (int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ *) ; 
 int ice_aq_stop_lldp (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int ice_cfg_lldp_mib_change (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ice_cfg_sw_lldp (struct ice_vsi*,int,int) ; 
 struct ice_priv_flag* ice_gstrings_priv_flags ; 
 int ice_init_pf_dcb (struct ice_pf*,int) ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  orig_flags ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ice_set_priv_flags(struct net_device *netdev, u32 flags)
{
	struct ice_netdev_priv *np = netdev_priv(netdev);
	DECLARE_BITMAP(change_flags, ICE_PF_FLAGS_NBITS);
	DECLARE_BITMAP(orig_flags, ICE_PF_FLAGS_NBITS);
	struct ice_vsi *vsi = np->vsi;
	struct ice_pf *pf = vsi->back;
	int ret = 0;
	u32 i;

	if (flags > BIT(ICE_PRIV_FLAG_ARRAY_SIZE))
		return -EINVAL;

	set_bit(ICE_FLAG_ETHTOOL_CTXT, pf->flags);

	bitmap_copy(orig_flags, pf->flags, ICE_PF_FLAGS_NBITS);
	for (i = 0; i < ICE_PRIV_FLAG_ARRAY_SIZE; i++) {
		const struct ice_priv_flag *priv_flag;

		priv_flag = &ice_gstrings_priv_flags[i];

		if (flags & BIT(i))
			set_bit(priv_flag->bitno, pf->flags);
		else
			clear_bit(priv_flag->bitno, pf->flags);
	}

	bitmap_xor(change_flags, pf->flags, orig_flags, ICE_PF_FLAGS_NBITS);

	if (test_bit(ICE_FLAG_FW_LLDP_AGENT, change_flags)) {
		if (!test_bit(ICE_FLAG_FW_LLDP_AGENT, pf->flags)) {
			enum ice_status status;

			/* Disable FW LLDP engine */
			status = ice_cfg_lldp_mib_change(&pf->hw, false);

			/* If unregistering for LLDP events fails, this is
			 * not an error state, as there shouldn't be any
			 * events to respond to.
			 */
			if (status)
				dev_info(&pf->pdev->dev,
					 "Failed to unreg for LLDP events\n");

			/* The AQ call to stop the FW LLDP agent will generate
			 * an error if the agent is already stopped.
			 */
			status = ice_aq_stop_lldp(&pf->hw, true, true, NULL);
			if (status)
				dev_warn(&pf->pdev->dev,
					 "Fail to stop LLDP agent\n");
			/* Use case for having the FW LLDP agent stopped
			 * will likely not need DCB, so failure to init is
			 * not a concern of ethtool
			 */
			status = ice_init_pf_dcb(pf, true);
			if (status)
				dev_warn(&pf->pdev->dev, "Fail to init DCB\n");

			/* Forward LLDP packets to default VSI so that they
			 * are passed up the stack
			 */
			ice_cfg_sw_lldp(vsi, false, true);
		} else {
			enum ice_status status;
			bool dcbx_agent_status;

			/* AQ command to start FW LLDP agent will return an
			 * error if the agent is already started
			 */
			status = ice_aq_start_lldp(&pf->hw, true, NULL);
			if (status)
				dev_warn(&pf->pdev->dev,
					 "Fail to start LLDP Agent\n");

			/* AQ command to start FW DCBX agent will fail if
			 * the agent is already started
			 */
			status = ice_aq_start_stop_dcbx(&pf->hw, true,
							&dcbx_agent_status,
							NULL);
			if (status)
				dev_dbg(&pf->pdev->dev,
					"Failed to start FW DCBX\n");

			dev_info(&pf->pdev->dev, "FW DCBX agent is %s\n",
				 dcbx_agent_status ? "ACTIVE" : "DISABLED");

			/* Failure to configure MIB change or init DCB is not
			 * relevant to ethtool.  Print notification that
			 * registration/init failed but do not return error
			 * state to ethtool
			 */
			status = ice_init_pf_dcb(pf, true);
			if (status)
				dev_dbg(&pf->pdev->dev, "Fail to init DCB\n");

			/* Remove rule to direct LLDP packets to default VSI.
			 * The FW LLDP engine will now be consuming them.
			 */
			ice_cfg_sw_lldp(vsi, false, false);

			/* Register for MIB change events */
			status = ice_cfg_lldp_mib_change(&pf->hw, true);
			if (status)
				dev_dbg(&pf->pdev->dev,
					"Fail to enable MIB change events\n");
		}
	}
	clear_bit(ICE_FLAG_ETHTOOL_CTXT, pf->flags);
	return ret;
}