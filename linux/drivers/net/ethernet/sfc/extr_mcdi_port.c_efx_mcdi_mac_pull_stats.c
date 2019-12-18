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
struct TYPE_2__ {scalar_t__* addr; } ;
struct efx_nic {int num_mac_stats; TYPE_1__ stats_buffer; } ;
typedef  scalar_t__ __le64 ;

/* Variables and functions */
 int EFX_MAC_STATS_WAIT_ATTEMPTS ; 
 int /*<<< orphan*/  EFX_MAC_STATS_WAIT_US ; 
 scalar_t__ EFX_MC_STATS_GENERATION_INVALID ; 
 int /*<<< orphan*/  EFX_STATS_PULL ; 
 int /*<<< orphan*/  efx_mcdi_mac_stats (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

void efx_mcdi_mac_pull_stats(struct efx_nic *efx)
{
	__le64 *dma_stats = efx->stats_buffer.addr;
	int attempts = EFX_MAC_STATS_WAIT_ATTEMPTS;

	dma_stats[efx->num_mac_stats - 1] = EFX_MC_STATS_GENERATION_INVALID;
	efx_mcdi_mac_stats(efx, EFX_STATS_PULL, 0);

	while (dma_stats[efx->num_mac_stats - 1] ==
				EFX_MC_STATS_GENERATION_INVALID &&
			attempts-- != 0)
		udelay(EFX_MAC_STATS_WAIT_US);
}