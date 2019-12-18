#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  context_id; } ;
struct efx_nic {unsigned int vf_count; TYPE_1__ rss_context; struct efx_ef10_nic_data* nic_data; } ;
struct efx_ef10_nic_data {int must_realloc_vis; int must_restore_rss_contexts; int must_restore_filters; int must_restore_piobufs; int must_probe_vswitching; TYPE_2__* vf; int /*<<< orphan*/  vport_id; } ;
struct TYPE_4__ {scalar_t__ vport_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_EF10_RSS_CONTEXT_INVALID ; 
 int /*<<< orphan*/  EVB_PORT_ID_ASSIGNED ; 
 int /*<<< orphan*/  efx_ef10_forget_old_piobufs (struct efx_nic*) ; 

__attribute__((used)) static void efx_ef10_reset_mc_allocations(struct efx_nic *efx)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;
#ifdef CONFIG_SFC_SRIOV
	unsigned int i;
#endif

	/* All our allocations have been reset */
	nic_data->must_realloc_vis = true;
	nic_data->must_restore_rss_contexts = true;
	nic_data->must_restore_filters = true;
	nic_data->must_restore_piobufs = true;
	efx_ef10_forget_old_piobufs(efx);
	efx->rss_context.context_id = EFX_EF10_RSS_CONTEXT_INVALID;

	/* Driver-created vswitches and vports must be re-created */
	nic_data->must_probe_vswitching = true;
	nic_data->vport_id = EVB_PORT_ID_ASSIGNED;
#ifdef CONFIG_SFC_SRIOV
	if (nic_data->vf)
		for (i = 0; i < efx->vf_count; i++)
			nic_data->vf[i].vport_id = 0;
#endif
}