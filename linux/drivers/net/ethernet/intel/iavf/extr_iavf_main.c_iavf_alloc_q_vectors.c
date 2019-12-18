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
struct iavf_q_vector {int v_idx; int reg_idx; int /*<<< orphan*/  napi; int /*<<< orphan*/  affinity_mask; int /*<<< orphan*/ * vsi; struct iavf_adapter* adapter; } ;
struct iavf_adapter {int num_msix_vectors; int /*<<< orphan*/  netdev; int /*<<< orphan*/  vsi; struct iavf_q_vector* q_vectors; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NAPI_POLL_WEIGHT ; 
 int NONQ_VECS ; 
 int /*<<< orphan*/  cpu_possible_mask ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iavf_napi_poll ; 
 struct iavf_q_vector* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iavf_alloc_q_vectors(struct iavf_adapter *adapter)
{
	int q_idx = 0, num_q_vectors;
	struct iavf_q_vector *q_vector;

	num_q_vectors = adapter->num_msix_vectors - NONQ_VECS;
	adapter->q_vectors = kcalloc(num_q_vectors, sizeof(*q_vector),
				     GFP_KERNEL);
	if (!adapter->q_vectors)
		return -ENOMEM;

	for (q_idx = 0; q_idx < num_q_vectors; q_idx++) {
		q_vector = &adapter->q_vectors[q_idx];
		q_vector->adapter = adapter;
		q_vector->vsi = &adapter->vsi;
		q_vector->v_idx = q_idx;
		q_vector->reg_idx = q_idx;
		cpumask_copy(&q_vector->affinity_mask, cpu_possible_mask);
		netif_napi_add(adapter->netdev, &q_vector->napi,
			       iavf_napi_poll, NAPI_POLL_WEIGHT);
	}

	return 0;
}