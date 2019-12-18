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
struct i40e_vsi {int num_q_vectors; struct i40e_pf* back; } ;
struct i40e_pf {int flags; size_t lan_vsi; struct i40e_vsi** vsi; } ;

/* Variables and functions */
 int EINVAL ; 
 int I40E_FLAG_MSIX_ENABLED ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int cpumask_first (int /*<<< orphan*/ ) ; 
 int cpumask_next (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_free_q_vector (struct i40e_vsi*,int) ; 
 int i40e_vsi_alloc_q_vector (struct i40e_vsi*,int,int) ; 
 int nr_cpu_ids ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int i40e_vsi_alloc_q_vectors(struct i40e_vsi *vsi)
{
	struct i40e_pf *pf = vsi->back;
	int err, v_idx, num_q_vectors, current_cpu;

	/* if not MSIX, give the one vector only to the LAN VSI */
	if (pf->flags & I40E_FLAG_MSIX_ENABLED)
		num_q_vectors = vsi->num_q_vectors;
	else if (vsi == pf->vsi[pf->lan_vsi])
		num_q_vectors = 1;
	else
		return -EINVAL;

	current_cpu = cpumask_first(cpu_online_mask);

	for (v_idx = 0; v_idx < num_q_vectors; v_idx++) {
		err = i40e_vsi_alloc_q_vector(vsi, v_idx, current_cpu);
		if (err)
			goto err_out;
		current_cpu = cpumask_next(current_cpu, cpu_online_mask);
		if (unlikely(current_cpu >= nr_cpu_ids))
			current_cpu = cpumask_first(cpu_online_mask);
	}

	return 0;

err_out:
	while (v_idx--)
		i40e_free_q_vector(vsi, v_idx);

	return err;
}