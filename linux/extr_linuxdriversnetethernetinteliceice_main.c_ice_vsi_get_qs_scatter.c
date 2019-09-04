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
struct ice_vsi {scalar_t__ tx_mapping_mode; int alloc_txq; int* txq_map; scalar_t__ rx_mapping_mode; int alloc_rxq; int* rxq_map; struct ice_pf* back; } ;
struct ice_pf {int /*<<< orphan*/  avail_q_mutex; int /*<<< orphan*/  avail_txqs; int /*<<< orphan*/  avail_rxqs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ICE_MAX_RXQS ; 
 int ICE_MAX_TXQS ; 
 scalar_t__ ICE_VSI_MAP_SCATTER ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int find_next_zero_bit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ice_vsi_get_qs_scatter(struct ice_vsi *vsi)
{
	struct ice_pf *pf = vsi->back;
	int i, index = 0;

	mutex_lock(&pf->avail_q_mutex);

	if (vsi->tx_mapping_mode == ICE_VSI_MAP_SCATTER) {
		for (i = 0; i < vsi->alloc_txq; i++) {
			index = find_next_zero_bit(pf->avail_txqs,
						   ICE_MAX_TXQS, index);
			if (index < ICE_MAX_TXQS) {
				set_bit(index, pf->avail_txqs);
				vsi->txq_map[i] = index;
			} else {
				goto err_scatter_tx;
			}
		}
	}

	if (vsi->rx_mapping_mode == ICE_VSI_MAP_SCATTER) {
		for (i = 0; i < vsi->alloc_rxq; i++) {
			index = find_next_zero_bit(pf->avail_rxqs,
						   ICE_MAX_RXQS, index);
			if (index < ICE_MAX_RXQS) {
				set_bit(index, pf->avail_rxqs);
				vsi->rxq_map[i] = index;
			} else {
				goto err_scatter_rx;
			}
		}
	}

	mutex_unlock(&pf->avail_q_mutex);
	return 0;

err_scatter_rx:
	/* unflag any queues we have grabbed (i is failed position) */
	for (index = 0; index < i; index++) {
		clear_bit(vsi->rxq_map[index], pf->avail_rxqs);
		vsi->rxq_map[index] = 0;
	}
	i = vsi->alloc_txq;
err_scatter_tx:
	/* i is either position of failed attempt or vsi->alloc_txq */
	for (index = 0; index < i; index++) {
		clear_bit(vsi->txq_map[index], pf->avail_txqs);
		vsi->txq_map[index] = 0;
	}

	mutex_unlock(&pf->avail_q_mutex);
	return -ENOMEM;
}