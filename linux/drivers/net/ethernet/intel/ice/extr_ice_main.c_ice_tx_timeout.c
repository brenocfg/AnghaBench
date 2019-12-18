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
struct netdev_queue {unsigned long trans_start; } ;
struct net_device {size_t num_tx_queues; scalar_t__ watchdog_timeo; } ;
struct ice_vsi {size_t num_txq; int /*<<< orphan*/  state; int /*<<< orphan*/  vsi_num; int /*<<< orphan*/ * txq_map; struct ice_ring** tx_rings; struct ice_pf* back; } ;
struct ice_ring {int q_index; int /*<<< orphan*/  next_to_use; int /*<<< orphan*/  next_to_clean; TYPE_1__* q_vector; scalar_t__ desc; } ;
struct ice_hw {int dummy; } ;
struct ice_pf {int tx_timeout_recovery_level; int /*<<< orphan*/  state; scalar_t__ tx_timeout_last_recovery; struct ice_hw hw; int /*<<< orphan*/  tx_timeout_count; } ;
struct ice_netdev_priv {struct ice_vsi* vsi; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLINT_DYN_CTL (int /*<<< orphan*/ ) ; 
 int HZ ; 
 int /*<<< orphan*/  QTX_COMM_HEAD (int /*<<< orphan*/ ) ; 
 size_t QTX_COMM_HEAD_HEAD_M ; 
 size_t QTX_COMM_HEAD_HEAD_S ; 
 int /*<<< orphan*/  __ICE_CORER_REQ ; 
 int /*<<< orphan*/  __ICE_DOWN ; 
 int /*<<< orphan*/  __ICE_GLOBR_REQ ; 
 int /*<<< orphan*/  __ICE_NEEDS_RESTART ; 
 int /*<<< orphan*/  __ICE_PFR_REQ ; 
 int /*<<< orphan*/  __ICE_SERVICE_DIS ; 
 int /*<<< orphan*/  ice_service_task_schedule (struct ice_pf*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,size_t) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,...) ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_xmit_stopped (struct netdev_queue*) ; 
 size_t rd32 (struct ice_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void ice_tx_timeout(struct net_device *netdev)
{
	struct ice_netdev_priv *np = netdev_priv(netdev);
	struct ice_ring *tx_ring = NULL;
	struct ice_vsi *vsi = np->vsi;
	struct ice_pf *pf = vsi->back;
	int hung_queue = -1;
	u32 i;

	pf->tx_timeout_count++;

	/* find the stopped queue the same way dev_watchdog() does */
	for (i = 0; i < netdev->num_tx_queues; i++) {
		unsigned long trans_start;
		struct netdev_queue *q;

		q = netdev_get_tx_queue(netdev, i);
		trans_start = q->trans_start;
		if (netif_xmit_stopped(q) &&
		    time_after(jiffies,
			       trans_start + netdev->watchdog_timeo)) {
			hung_queue = i;
			break;
		}
	}

	if (i == netdev->num_tx_queues)
		netdev_info(netdev, "tx_timeout: no netdev hung queue found\n");
	else
		/* now that we have an index, find the tx_ring struct */
		for (i = 0; i < vsi->num_txq; i++)
			if (vsi->tx_rings[i] && vsi->tx_rings[i]->desc)
				if (hung_queue == vsi->tx_rings[i]->q_index) {
					tx_ring = vsi->tx_rings[i];
					break;
				}

	/* Reset recovery level if enough time has elapsed after last timeout.
	 * Also ensure no new reset action happens before next timeout period.
	 */
	if (time_after(jiffies, (pf->tx_timeout_last_recovery + HZ * 20)))
		pf->tx_timeout_recovery_level = 1;
	else if (time_before(jiffies, (pf->tx_timeout_last_recovery +
				       netdev->watchdog_timeo)))
		return;

	if (tx_ring) {
		struct ice_hw *hw = &pf->hw;
		u32 head, val = 0;

		head = (rd32(hw, QTX_COMM_HEAD(vsi->txq_map[hung_queue])) &
			QTX_COMM_HEAD_HEAD_M) >> QTX_COMM_HEAD_HEAD_S;
		/* Read interrupt register */
		val = rd32(hw, GLINT_DYN_CTL(tx_ring->q_vector->reg_idx));

		netdev_info(netdev, "tx_timeout: VSI_num: %d, Q %d, NTC: 0x%x, HW_HEAD: 0x%x, NTU: 0x%x, INT: 0x%x\n",
			    vsi->vsi_num, hung_queue, tx_ring->next_to_clean,
			    head, tx_ring->next_to_use, val);
	}

	pf->tx_timeout_last_recovery = jiffies;
	netdev_info(netdev, "tx_timeout recovery level %d, hung_queue %d\n",
		    pf->tx_timeout_recovery_level, hung_queue);

	switch (pf->tx_timeout_recovery_level) {
	case 1:
		set_bit(__ICE_PFR_REQ, pf->state);
		break;
	case 2:
		set_bit(__ICE_CORER_REQ, pf->state);
		break;
	case 3:
		set_bit(__ICE_GLOBR_REQ, pf->state);
		break;
	default:
		netdev_err(netdev, "tx_timeout recovery unsuccessful, device is in unrecoverable state.\n");
		set_bit(__ICE_DOWN, pf->state);
		set_bit(__ICE_NEEDS_RESTART, vsi->state);
		set_bit(__ICE_SERVICE_DIS, pf->state);
		break;
	}

	ice_service_task_schedule(pf);
	pf->tx_timeout_recovery_level++;
}