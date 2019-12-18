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
typedef  scalar_t__ u32 ;
struct siena_nic_data {scalar_t__* stats; } ;
struct efx_nic {struct siena_nic_data* nic_data; } ;
typedef  int /*<<< orphan*/  efx_dword_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_DWORD_0 ; 
 scalar_t__ EFX_DWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFX_ZERO_DWORD (int /*<<< orphan*/ ) ; 
 int EINTR ; 
 int EIO ; 
 unsigned int FR_CZ_MC_TREG_SMEM ; 
 unsigned int MCDI_STATUS (struct efx_nic*) ; 
 scalar_t__ MC_STATUS_DWORD_ASSERT ; 
 size_t SIENA_STAT_rx_good_bytes ; 
 size_t SIENA_STAT_tx_good_bytes ; 
 int /*<<< orphan*/  efx_readd (struct efx_nic*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  efx_writed (struct efx_nic*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int siena_mcdi_poll_reboot(struct efx_nic *efx)
{
	struct siena_nic_data *nic_data = efx->nic_data;
	unsigned int addr = FR_CZ_MC_TREG_SMEM + MCDI_STATUS(efx);
	efx_dword_t reg;
	u32 value;

	efx_readd(efx, &reg, addr);
	value = EFX_DWORD_FIELD(reg, EFX_DWORD_0);

	if (value == 0)
		return 0;

	EFX_ZERO_DWORD(reg);
	efx_writed(efx, &reg, addr);

	/* MAC statistics have been cleared on the NIC; clear the local
	 * copies that we update with efx_update_diff_stat().
	 */
	nic_data->stats[SIENA_STAT_tx_good_bytes] = 0;
	nic_data->stats[SIENA_STAT_rx_good_bytes] = 0;

	if (value == MC_STATUS_DWORD_ASSERT)
		return -EINTR;
	else
		return -EIO;
}