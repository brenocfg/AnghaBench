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
struct efx_nic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_STATS_DISABLE ; 
 int /*<<< orphan*/  efx_mcdi_mac_stats (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void efx_mcdi_mac_stop_stats(struct efx_nic *efx)
{
	efx_mcdi_mac_stats(efx, EFX_STATS_DISABLE, 0);
}