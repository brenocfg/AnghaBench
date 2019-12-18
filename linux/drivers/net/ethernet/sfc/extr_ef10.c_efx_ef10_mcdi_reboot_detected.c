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
struct efx_nic {struct efx_ef10_nic_data* nic_data; } ;
struct efx_ef10_nic_data {int must_check_datapath_caps; scalar_t__* stats; } ;

/* Variables and functions */
 size_t EF10_STAT_port_rx_bad_bytes ; 
 int /*<<< orphan*/  efx_ef10_reset_mc_allocations (struct efx_nic*) ; 

__attribute__((used)) static void efx_ef10_mcdi_reboot_detected(struct efx_nic *efx)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;

	/* All our allocations have been reset */
	efx_ef10_reset_mc_allocations(efx);

	/* The datapath firmware might have been changed */
	nic_data->must_check_datapath_caps = true;

	/* MAC statistics have been cleared on the NIC; clear the local
	 * statistic that we update with efx_update_diff_stat().
	 */
	nic_data->stats[EF10_STAT_port_rx_bad_bytes] = 0;
}