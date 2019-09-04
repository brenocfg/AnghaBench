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
struct i40e_vsi {struct i40e_q_vector** q_vectors; scalar_t__ netdev; } ;
struct i40e_q_vector {int v_idx; int /*<<< orphan*/  napi; int /*<<< orphan*/  affinity_mask; struct i40e_vsi* vsi; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NAPI_POLL_WEIGHT ; 
 int /*<<< orphan*/  cpu_possible_mask ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_napi_poll ; 
 struct i40e_q_vector* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_napi_add (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40e_vsi_alloc_q_vector(struct i40e_vsi *vsi, int v_idx, int cpu)
{
	struct i40e_q_vector *q_vector;

	/* allocate q_vector */
	q_vector = kzalloc(sizeof(struct i40e_q_vector), GFP_KERNEL);
	if (!q_vector)
		return -ENOMEM;

	q_vector->vsi = vsi;
	q_vector->v_idx = v_idx;
	cpumask_copy(&q_vector->affinity_mask, cpu_possible_mask);

	if (vsi->netdev)
		netif_napi_add(vsi->netdev, &q_vector->napi,
			       i40e_napi_poll, NAPI_POLL_WEIGHT);

	/* tie q_vector and vsi together */
	vsi->q_vectors[v_idx] = q_vector;

	return 0;
}