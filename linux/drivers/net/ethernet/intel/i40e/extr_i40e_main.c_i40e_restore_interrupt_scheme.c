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
struct i40e_pf {int flags; int num_alloc_vsi; scalar_t__* vsi; } ;

/* Variables and functions */
 int I40E_FLAG_IWARP_ENABLED ; 
 int I40E_FLAG_MSIX_ENABLED ; 
 int I40E_FLAG_MSI_ENABLED ; 
 int /*<<< orphan*/  i40e_client_update_msix_info (struct i40e_pf*) ; 
 int i40e_init_interrupt_scheme (struct i40e_pf*) ; 
 int i40e_setup_misc_vector (struct i40e_pf*) ; 
 int i40e_vsi_alloc_q_vectors (scalar_t__) ; 
 int /*<<< orphan*/  i40e_vsi_free_q_vectors (scalar_t__) ; 
 int /*<<< orphan*/  i40e_vsi_map_rings_to_vectors (scalar_t__) ; 

__attribute__((used)) static int i40e_restore_interrupt_scheme(struct i40e_pf *pf)
{
	int err, i;

	/* We cleared the MSI and MSI-X flags when disabling the old interrupt
	 * scheme. We need to re-enabled them here in order to attempt to
	 * re-acquire the MSI or MSI-X vectors
	 */
	pf->flags |= (I40E_FLAG_MSIX_ENABLED | I40E_FLAG_MSI_ENABLED);

	err = i40e_init_interrupt_scheme(pf);
	if (err)
		return err;

	/* Now that we've re-acquired IRQs, we need to remap the vectors and
	 * rings together again.
	 */
	for (i = 0; i < pf->num_alloc_vsi; i++) {
		if (pf->vsi[i]) {
			err = i40e_vsi_alloc_q_vectors(pf->vsi[i]);
			if (err)
				goto err_unwind;
			i40e_vsi_map_rings_to_vectors(pf->vsi[i]);
		}
	}

	err = i40e_setup_misc_vector(pf);
	if (err)
		goto err_unwind;

	if (pf->flags & I40E_FLAG_IWARP_ENABLED)
		i40e_client_update_msix_info(pf);

	return 0;

err_unwind:
	while (i--) {
		if (pf->vsi[i])
			i40e_vsi_free_q_vectors(pf->vsi[i]);
	}

	return err;
}