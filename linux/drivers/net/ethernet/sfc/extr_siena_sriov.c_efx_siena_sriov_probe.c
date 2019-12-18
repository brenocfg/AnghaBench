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
struct efx_nic {unsigned int vf_count; int /*<<< orphan*/ ** extra_channel_type; int /*<<< orphan*/  net_dev; int /*<<< orphan*/  vi_scale; } ;

/* Variables and functions */
 size_t EFX_EXTRA_CHANNEL_IOV ; 
 int /*<<< orphan*/  efx_siena_sriov_channel_type ; 
 scalar_t__ efx_siena_sriov_cmd (struct efx_nic*,int,int /*<<< orphan*/ *,unsigned int*) ; 
 unsigned int max_vfs ; 
 int /*<<< orphan*/  netif_info (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  probe ; 

void efx_siena_sriov_probe(struct efx_nic *efx)
{
	unsigned count;

	if (!max_vfs)
		return;

	if (efx_siena_sriov_cmd(efx, false, &efx->vi_scale, &count)) {
		netif_info(efx, probe, efx->net_dev, "no SR-IOV VFs probed\n");
		return;
	}
	if (count > 0 && count > max_vfs)
		count = max_vfs;

	/* efx_nic_dimension_resources() will reduce vf_count as appopriate */
	efx->vf_count = count;

	efx->extra_channel_type[EFX_EXTRA_CHANNEL_IOV] = &efx_siena_sriov_channel_type;
}