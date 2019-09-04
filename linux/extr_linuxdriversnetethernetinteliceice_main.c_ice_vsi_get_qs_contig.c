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
struct ice_vsi {int alloc_txq; int* txq_map; int alloc_rxq; int* rxq_map; void* rx_mapping_mode; void* tx_mapping_mode; struct ice_pf* back; } ;
struct ice_pf {int /*<<< orphan*/  avail_q_mutex; int /*<<< orphan*/  avail_rxqs; int /*<<< orphan*/  avail_txqs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ICE_MAX_RXQS ; 
 int ICE_MAX_TXQS ; 
 void* ICE_VSI_MAP_SCATTER ; 
 int bitmap_find_next_zero_area (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ice_vsi_get_qs_contig(struct ice_vsi *vsi)
{
	struct ice_pf *pf = vsi->back;
	int offset, ret = 0;

	mutex_lock(&pf->avail_q_mutex);
	/* look for contiguous block of queues for tx */
	offset = bitmap_find_next_zero_area(pf->avail_txqs, ICE_MAX_TXQS,
					    0, vsi->alloc_txq, 0);
	if (offset < ICE_MAX_TXQS) {
		int i;

		bitmap_set(pf->avail_txqs, offset, vsi->alloc_txq);
		for (i = 0; i < vsi->alloc_txq; i++)
			vsi->txq_map[i] = i + offset;
	} else {
		ret = -ENOMEM;
		vsi->tx_mapping_mode = ICE_VSI_MAP_SCATTER;
	}

	/* look for contiguous block of queues for rx */
	offset = bitmap_find_next_zero_area(pf->avail_rxqs, ICE_MAX_RXQS,
					    0, vsi->alloc_rxq, 0);
	if (offset < ICE_MAX_RXQS) {
		int i;

		bitmap_set(pf->avail_rxqs, offset, vsi->alloc_rxq);
		for (i = 0; i < vsi->alloc_rxq; i++)
			vsi->rxq_map[i] = i + offset;
	} else {
		ret = -ENOMEM;
		vsi->rx_mapping_mode = ICE_VSI_MAP_SCATTER;
	}
	mutex_unlock(&pf->avail_q_mutex);

	return ret;
}