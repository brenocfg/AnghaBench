#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct ice_vsi {int /*<<< orphan*/  netdev; struct ice_pf* back; } ;
struct ice_ring_container {int itr_setting; int /*<<< orphan*/  target_itr; TYPE_2__* ring; } ;
struct TYPE_8__ {int /*<<< orphan*/  intrl_gran; } ;
struct ice_pf {TYPE_3__* pdev; TYPE_4__ hw; } ;
struct ethtool_coalesce {int use_adaptive_rx_coalesce; int rx_coalesce_usecs; int use_adaptive_tx_coalesce; int tx_coalesce_usecs; int /*<<< orphan*/  tx_coalesce_usecs_high; int /*<<< orphan*/  rx_coalesce_usecs_high; } ;
typedef  enum ice_container_type { ____Placeholder_ice_container_type } ice_container_type ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {TYPE_1__* q_vector; } ;
struct TYPE_5__ {int /*<<< orphan*/  reg_idx; int /*<<< orphan*/  intrl; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GLINT_RATE (int /*<<< orphan*/ ) ; 
 int ICE_ITR_DYNAMIC ; 
 int ICE_ITR_MAX ; 
 int /*<<< orphan*/  ICE_MAX_INTRL ; 
#define  ICE_RX_CONTAINER 129 
#define  ICE_TX_CONTAINER 128 
 int /*<<< orphan*/  ITR_REG_ALIGN (int) ; 
 int /*<<< orphan*/  ITR_TO_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ice_intrl_usec_to_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  wr32 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ice_set_rc_coalesce(enum ice_container_type c_type, struct ethtool_coalesce *ec,
		    struct ice_ring_container *rc, struct ice_vsi *vsi)
{
	const char *c_type_str = (c_type == ICE_RX_CONTAINER) ? "rx" : "tx";
	u32 use_adaptive_coalesce, coalesce_usecs;
	struct ice_pf *pf = vsi->back;
	u16 itr_setting;

	if (!rc->ring)
		return -EINVAL;

	switch (c_type) {
	case ICE_RX_CONTAINER:
		if (ec->rx_coalesce_usecs_high > ICE_MAX_INTRL ||
		    (ec->rx_coalesce_usecs_high &&
		     ec->rx_coalesce_usecs_high < pf->hw.intrl_gran)) {
			netdev_info(vsi->netdev,
				    "Invalid value, %s-usecs-high valid values are 0 (disabled), %d-%d\n",
				    c_type_str, pf->hw.intrl_gran,
				    ICE_MAX_INTRL);
			return -EINVAL;
		}
		if (ec->rx_coalesce_usecs_high != rc->ring->q_vector->intrl) {
			rc->ring->q_vector->intrl = ec->rx_coalesce_usecs_high;
			wr32(&pf->hw, GLINT_RATE(rc->ring->q_vector->reg_idx),
			     ice_intrl_usec_to_reg(ec->rx_coalesce_usecs_high,
						   pf->hw.intrl_gran));
		}

		use_adaptive_coalesce = ec->use_adaptive_rx_coalesce;
		coalesce_usecs = ec->rx_coalesce_usecs;

		break;
	case ICE_TX_CONTAINER:
		if (ec->tx_coalesce_usecs_high) {
			netdev_info(vsi->netdev,
				    "setting %s-usecs-high is not supported\n",
				    c_type_str);
			return -EINVAL;
		}

		use_adaptive_coalesce = ec->use_adaptive_tx_coalesce;
		coalesce_usecs = ec->tx_coalesce_usecs;

		break;
	default:
		dev_dbg(&pf->pdev->dev, "Invalid container type %d\n", c_type);
		return -EINVAL;
	}

	itr_setting = rc->itr_setting & ~ICE_ITR_DYNAMIC;
	if (coalesce_usecs != itr_setting && use_adaptive_coalesce) {
		netdev_info(vsi->netdev,
			    "%s interrupt throttling cannot be changed if adaptive-%s is enabled\n",
			    c_type_str, c_type_str);
		return -EINVAL;
	}

	if (coalesce_usecs > ICE_ITR_MAX) {
		netdev_info(vsi->netdev,
			    "Invalid value, %s-usecs range is 0-%d\n",
			    c_type_str, ICE_ITR_MAX);
		return -EINVAL;
	}

	/* hardware only supports an ITR granularity of 2us */
	if (coalesce_usecs % 2 != 0) {
		netdev_info(vsi->netdev,
			    "Invalid value, %s-usecs must be even\n",
			    c_type_str);
		return -EINVAL;
	}

	if (use_adaptive_coalesce) {
		rc->itr_setting |= ICE_ITR_DYNAMIC;
	} else {
		/* store user facing value how it was set */
		rc->itr_setting = coalesce_usecs;
		/* set to static and convert to value HW understands */
		rc->target_itr =
			ITR_TO_REG(ITR_REG_ALIGN(rc->itr_setting));
	}

	return 0;
}