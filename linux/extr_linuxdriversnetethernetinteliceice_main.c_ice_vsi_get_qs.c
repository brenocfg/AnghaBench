#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ice_vsi {scalar_t__ tx_mapping_mode; scalar_t__ rx_mapping_mode; void* alloc_rxq; void* alloc_txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_MAX_SCATTER_RXQS ; 
 int /*<<< orphan*/  ICE_MAX_SCATTER_TXQS ; 
 void* ICE_VSI_MAP_CONTIG ; 
 scalar_t__ ICE_VSI_MAP_SCATTER ; 
 int ice_vsi_get_qs_contig (struct ice_vsi*) ; 
 int ice_vsi_get_qs_scatter (struct ice_vsi*) ; 
 void* max_t (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u16 ; 

__attribute__((used)) static int ice_vsi_get_qs(struct ice_vsi *vsi)
{
	int ret = 0;

	vsi->tx_mapping_mode = ICE_VSI_MAP_CONTIG;
	vsi->rx_mapping_mode = ICE_VSI_MAP_CONTIG;

	/* NOTE: ice_vsi_get_qs_contig() will set the rx/tx mapping
	 * modes individually to scatter if assigning contiguous queues
	 * to rx or tx fails
	 */
	ret = ice_vsi_get_qs_contig(vsi);
	if (ret < 0) {
		if (vsi->tx_mapping_mode == ICE_VSI_MAP_SCATTER)
			vsi->alloc_txq = max_t(u16, vsi->alloc_txq,
					       ICE_MAX_SCATTER_TXQS);
		if (vsi->rx_mapping_mode == ICE_VSI_MAP_SCATTER)
			vsi->alloc_rxq = max_t(u16, vsi->alloc_rxq,
					       ICE_MAX_SCATTER_RXQS);
		ret = ice_vsi_get_qs_scatter(vsi);
	}

	return ret;
}