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
struct ice_vsi {int num_rxq; int num_txq; TYPE_4__** tx_rings; TYPE_2__** rx_rings; } ;
struct ethtool_coalesce {int dummy; } ;
struct TYPE_8__ {TYPE_3__* q_vector; } ;
struct TYPE_7__ {int /*<<< orphan*/  tx; } ;
struct TYPE_6__ {TYPE_1__* q_vector; } ;
struct TYPE_5__ {int /*<<< orphan*/  rx; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ICE_RX_CONTAINER ; 
 int /*<<< orphan*/  ICE_TX_CONTAINER ; 
 scalar_t__ ice_set_rc_coalesce (int /*<<< orphan*/ ,struct ethtool_coalesce*,int /*<<< orphan*/ *,struct ice_vsi*) ; 

__attribute__((used)) static int
ice_set_q_coalesce(struct ice_vsi *vsi, struct ethtool_coalesce *ec, int q_num)
{
	if (q_num < vsi->num_rxq && q_num < vsi->num_txq) {
		if (ice_set_rc_coalesce(ICE_RX_CONTAINER, ec,
					&vsi->rx_rings[q_num]->q_vector->rx,
					vsi))
			return -EINVAL;

		if (ice_set_rc_coalesce(ICE_TX_CONTAINER, ec,
					&vsi->tx_rings[q_num]->q_vector->tx,
					vsi))
			return -EINVAL;
	} else if (q_num < vsi->num_rxq) {
		if (ice_set_rc_coalesce(ICE_RX_CONTAINER, ec,
					&vsi->rx_rings[q_num]->q_vector->rx,
					vsi))
			return -EINVAL;
	} else if (q_num < vsi->num_txq) {
		if (ice_set_rc_coalesce(ICE_TX_CONTAINER, ec,
					&vsi->tx_rings[q_num]->q_vector->tx,
					vsi))
			return -EINVAL;
	} else {
		return -EINVAL;
	}

	return 0;
}