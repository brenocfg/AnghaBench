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
struct bnx2x_nig_brb_pfc_port_params {int num_of_rx_cos_priority_mask; int* rx_cos_priority_mask; int pkt_priority_to_cos; int llfc_low_priority_classes; scalar_t__ llfc_high_priority_classes; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int /*<<< orphan*/  feature_config_flags; } ;
struct TYPE_6__ {int num_of_cos; TYPE_1__* cos_params; } ;
struct TYPE_7__ {TYPE_2__ ets; } ;
struct bnx2x {int /*<<< orphan*/  link_vars; TYPE_4__ link_params; TYPE_3__ dcbx_port_params; } ;
struct TYPE_5__ {int pri_bitmask; } ;

/* Variables and functions */
 int DCBX_PFC_PRI_PAUSE_MASK (struct bnx2x*) ; 
 int /*<<< orphan*/  FEATURE_CONFIG_PFC_ENABLED ; 
 int MAX_PFC_PRIORITIES ; 
 int /*<<< orphan*/  bnx2x_acquire_phy_lock (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_release_phy_lock (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_update_pfc (TYPE_4__*,int /*<<< orphan*/ *,struct bnx2x_nig_brb_pfc_port_params*) ; 

__attribute__((used)) static void bnx2x_pfc_set(struct bnx2x *bp)
{
	struct bnx2x_nig_brb_pfc_port_params pfc_params = {0};
	u32 pri_bit, val = 0;
	int i;

	pfc_params.num_of_rx_cos_priority_mask =
					bp->dcbx_port_params.ets.num_of_cos;

	/* Tx COS configuration */
	for (i = 0; i < bp->dcbx_port_params.ets.num_of_cos; i++)
		/*
		 * We configure only the pauseable bits (non pauseable aren't
		 * configured at all) it's done to avoid false pauses from
		 * network
		 */
		pfc_params.rx_cos_priority_mask[i] =
			bp->dcbx_port_params.ets.cos_params[i].pri_bitmask
				& DCBX_PFC_PRI_PAUSE_MASK(bp);

	/*
	 * Rx COS configuration
	 * Changing PFC RX configuration .
	 * In RX COS0 will always be configured to lossless and COS1 to lossy
	 */
	for (i = 0 ; i < MAX_PFC_PRIORITIES ; i++) {
		pri_bit = 1 << i;

		if (!(pri_bit & DCBX_PFC_PRI_PAUSE_MASK(bp)))
			val |= 1 << (i * 4);
	}

	pfc_params.pkt_priority_to_cos = val;

	/* RX COS0 */
	pfc_params.llfc_low_priority_classes = DCBX_PFC_PRI_PAUSE_MASK(bp);
	/* RX COS1 */
	pfc_params.llfc_high_priority_classes = 0;

	bnx2x_acquire_phy_lock(bp);
	bp->link_params.feature_config_flags |= FEATURE_CONFIG_PFC_ENABLED;
	bnx2x_update_pfc(&bp->link_params, &bp->link_vars, &pfc_params);
	bnx2x_release_phy_lock(bp);
}