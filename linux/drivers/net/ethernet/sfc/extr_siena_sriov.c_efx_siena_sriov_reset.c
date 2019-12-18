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
struct siena_vf {int dummy; } ;
struct siena_nic_data {struct siena_vf* vf; } ;
struct efx_nic {unsigned int vf_init_count; struct siena_nic_data* nic_data; } ;
struct efx_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  EFX_PAGE_SIZE ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 scalar_t__ efx_nic_alloc_buffer (struct efx_nic*,struct efx_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_nic_free_buffer (struct efx_nic*,struct efx_buffer*) ; 
 int /*<<< orphan*/  efx_siena_sriov_cmd (struct efx_nic*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_siena_sriov_reset_vf (struct siena_vf*,struct efx_buffer*) ; 
 int /*<<< orphan*/  efx_siena_sriov_usrev (struct efx_nic*,int) ; 

void efx_siena_sriov_reset(struct efx_nic *efx)
{
	struct siena_nic_data *nic_data = efx->nic_data;
	unsigned int vf_i;
	struct efx_buffer buf;
	struct siena_vf *vf;

	ASSERT_RTNL();

	if (efx->vf_init_count == 0)
		return;

	efx_siena_sriov_usrev(efx, true);
	(void)efx_siena_sriov_cmd(efx, true, NULL, NULL);

	if (efx_nic_alloc_buffer(efx, &buf, EFX_PAGE_SIZE, GFP_NOIO))
		return;

	for (vf_i = 0; vf_i < efx->vf_init_count; ++vf_i) {
		vf = nic_data->vf + vf_i;
		efx_siena_sriov_reset_vf(vf, &buf);
	}

	efx_nic_free_buffer(efx, &buf);
}