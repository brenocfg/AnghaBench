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
struct ice_vsi {scalar_t__ type; struct ice_q_vector** q_vectors; scalar_t__ netdev; struct ice_pf* back; } ;
struct ice_q_vector {int v_idx; int /*<<< orphan*/  napi; int /*<<< orphan*/  affinity_mask; struct ice_vsi* vsi; } ;
struct ice_pf {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ ICE_VSI_VF ; 
 int /*<<< orphan*/  NAPI_POLL_WEIGHT ; 
 scalar_t__ cpu_online (int) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ *) ; 
 struct ice_q_vector* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_napi_poll ; 
 int /*<<< orphan*/  netif_napi_add (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ice_vsi_alloc_q_vector(struct ice_vsi *vsi, int v_idx)
{
	struct ice_pf *pf = vsi->back;
	struct ice_q_vector *q_vector;

	/* allocate q_vector */
	q_vector = devm_kzalloc(&pf->pdev->dev, sizeof(*q_vector), GFP_KERNEL);
	if (!q_vector)
		return -ENOMEM;

	q_vector->vsi = vsi;
	q_vector->v_idx = v_idx;
	if (vsi->type == ICE_VSI_VF)
		goto out;
	/* only set affinity_mask if the CPU is online */
	if (cpu_online(v_idx))
		cpumask_set_cpu(v_idx, &q_vector->affinity_mask);

	/* This will not be called in the driver load path because the netdev
	 * will not be created yet. All other cases with register the NAPI
	 * handler here (i.e. resume, reset/rebuild, etc.)
	 */
	if (vsi->netdev)
		netif_napi_add(vsi->netdev, &q_vector->napi, ice_napi_poll,
			       NAPI_POLL_WEIGHT);

out:
	/* tie q_vector and VSI together */
	vsi->q_vectors[v_idx] = q_vector;

	return 0;
}