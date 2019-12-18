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
struct ice_vsi {void* rx_mapping_mode; void* tx_mapping_mode; int /*<<< orphan*/  rxq_map; int /*<<< orphan*/  alloc_rxq; int /*<<< orphan*/  txq_map; int /*<<< orphan*/  alloc_txq; struct ice_pf* back; } ;
struct ice_qs_cfg {void* mapping_mode; int /*<<< orphan*/  vsi_map_offset; int /*<<< orphan*/  vsi_map; int /*<<< orphan*/  scatter_count; int /*<<< orphan*/  q_count; int /*<<< orphan*/  pf_map_size; int /*<<< orphan*/  pf_map; int /*<<< orphan*/ * qs_mutex; } ;
struct ice_pf {int /*<<< orphan*/  max_pf_rxqs; int /*<<< orphan*/  avail_rxqs; int /*<<< orphan*/  avail_q_mutex; int /*<<< orphan*/  max_pf_txqs; int /*<<< orphan*/  avail_txqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_MAX_SCATTER_RXQS ; 
 int /*<<< orphan*/  ICE_MAX_SCATTER_TXQS ; 
 void* ICE_VSI_MAP_CONTIG ; 
 int __ice_vsi_get_qs (struct ice_qs_cfg*) ; 

__attribute__((used)) static int ice_vsi_get_qs(struct ice_vsi *vsi)
{
	struct ice_pf *pf = vsi->back;
	struct ice_qs_cfg tx_qs_cfg = {
		.qs_mutex = &pf->avail_q_mutex,
		.pf_map = pf->avail_txqs,
		.pf_map_size = pf->max_pf_txqs,
		.q_count = vsi->alloc_txq,
		.scatter_count = ICE_MAX_SCATTER_TXQS,
		.vsi_map = vsi->txq_map,
		.vsi_map_offset = 0,
		.mapping_mode = vsi->tx_mapping_mode
	};
	struct ice_qs_cfg rx_qs_cfg = {
		.qs_mutex = &pf->avail_q_mutex,
		.pf_map = pf->avail_rxqs,
		.pf_map_size = pf->max_pf_rxqs,
		.q_count = vsi->alloc_rxq,
		.scatter_count = ICE_MAX_SCATTER_RXQS,
		.vsi_map = vsi->rxq_map,
		.vsi_map_offset = 0,
		.mapping_mode = vsi->rx_mapping_mode
	};
	int ret = 0;

	vsi->tx_mapping_mode = ICE_VSI_MAP_CONTIG;
	vsi->rx_mapping_mode = ICE_VSI_MAP_CONTIG;

	ret = __ice_vsi_get_qs(&tx_qs_cfg);
	if (!ret)
		ret = __ice_vsi_get_qs(&rx_qs_cfg);

	return ret;
}