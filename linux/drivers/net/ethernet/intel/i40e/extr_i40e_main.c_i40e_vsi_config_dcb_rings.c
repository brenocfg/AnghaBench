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
typedef  int u16 ;
struct TYPE_6__ {int enabled_tc; TYPE_2__* tc_info; } ;
struct i40e_vsi {int num_queue_pairs; struct i40e_ring** tx_rings; struct i40e_ring** rx_rings; TYPE_3__ tc_config; TYPE_1__* back; } ;
struct i40e_ring {int dcb_tc; } ;
struct TYPE_5__ {int qoffset; int qcount; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int I40E_FLAG_DCB_ENABLED ; 
 int I40E_MAX_TRAFFIC_CLASS ; 

__attribute__((used)) static void i40e_vsi_config_dcb_rings(struct i40e_vsi *vsi)
{
	struct i40e_ring *tx_ring, *rx_ring;
	u16 qoffset, qcount;
	int i, n;

	if (!(vsi->back->flags & I40E_FLAG_DCB_ENABLED)) {
		/* Reset the TC information */
		for (i = 0; i < vsi->num_queue_pairs; i++) {
			rx_ring = vsi->rx_rings[i];
			tx_ring = vsi->tx_rings[i];
			rx_ring->dcb_tc = 0;
			tx_ring->dcb_tc = 0;
		}
		return;
	}

	for (n = 0; n < I40E_MAX_TRAFFIC_CLASS; n++) {
		if (!(vsi->tc_config.enabled_tc & BIT_ULL(n)))
			continue;

		qoffset = vsi->tc_config.tc_info[n].qoffset;
		qcount = vsi->tc_config.tc_info[n].qcount;
		for (i = qoffset; i < (qoffset + qcount); i++) {
			rx_ring = vsi->rx_rings[i];
			tx_ring = vsi->tx_rings[i];
			rx_ring->dcb_tc = n;
			tx_ring->dcb_tc = n;
		}
	}
}