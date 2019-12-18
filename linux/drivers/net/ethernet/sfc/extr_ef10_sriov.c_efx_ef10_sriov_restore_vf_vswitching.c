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
struct efx_nic {unsigned int vf_count; } ;

/* Variables and functions */
 int efx_ef10_sriov_assign_vf_vport (struct efx_nic*,unsigned int) ; 
 int /*<<< orphan*/  efx_ef10_sriov_free_vf_vswitching (struct efx_nic*) ; 

__attribute__((used)) static int efx_ef10_sriov_restore_vf_vswitching(struct efx_nic *efx)
{
	unsigned int i;
	int rc;

	for (i = 0; i < efx->vf_count; i++) {
		rc = efx_ef10_sriov_assign_vf_vport(efx, i);
		if (rc)
			goto fail;
	}

	return 0;
fail:
	efx_ef10_sriov_free_vf_vswitching(efx);
	return rc;
}