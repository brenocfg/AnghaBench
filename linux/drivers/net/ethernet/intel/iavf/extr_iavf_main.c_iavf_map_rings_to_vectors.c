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
struct iavf_adapter {int num_active_queues; int num_msix_vectors; int /*<<< orphan*/  aq_required; } ;

/* Variables and functions */
 int /*<<< orphan*/  IAVF_FLAG_AQ_MAP_VECTORS ; 
 int NONQ_VECS ; 
 int /*<<< orphan*/  iavf_map_vector_to_rxq (struct iavf_adapter*,int,int) ; 
 int /*<<< orphan*/  iavf_map_vector_to_txq (struct iavf_adapter*,int,int) ; 

__attribute__((used)) static void iavf_map_rings_to_vectors(struct iavf_adapter *adapter)
{
	int rings_remaining = adapter->num_active_queues;
	int ridx = 0, vidx = 0;
	int q_vectors;

	q_vectors = adapter->num_msix_vectors - NONQ_VECS;

	for (; ridx < rings_remaining; ridx++) {
		iavf_map_vector_to_rxq(adapter, vidx, ridx);
		iavf_map_vector_to_txq(adapter, vidx, ridx);

		/* In the case where we have more queues than vectors, continue
		 * round-robin on vectors until all queues are mapped.
		 */
		if (++vidx >= q_vectors)
			vidx = 0;
	}

	adapter->aq_required |= IAVF_FLAG_AQ_MAP_VECTORS;
}