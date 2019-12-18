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
struct siena_nic_data {unsigned int vf_buftbl_base; } ;
struct efx_nic {unsigned int n_tx_channels; unsigned int n_extra_tx_channels; unsigned int n_rx_channels; unsigned int n_channels; unsigned int vi_scale; unsigned int vf_count; unsigned int tx_dc_base; unsigned int rx_dc_base; int /*<<< orphan*/  net_dev; TYPE_1__* type; struct siena_nic_data* nic_data; } ;
typedef  int /*<<< orphan*/  efx_qword_t ;
struct TYPE_2__ {scalar_t__ (* sriov_wanted ) (struct efx_nic*) ;} ;

/* Variables and functions */
 unsigned int EFX_BUF_SIZE ; 
 unsigned int EFX_MAX_DMAQ_SIZE ; 
 unsigned int EFX_MAX_EVQ_SIZE ; 
 unsigned int EFX_TXQ_TYPES ; 
 unsigned int EFX_VF_BUFTBL_PER_VI ; 
 unsigned int EFX_VI_BASE ; 
 unsigned int RX_DC_ENTRIES ; 
 unsigned int TX_DC_ENTRIES ; 
 unsigned int efx_vf_size (struct efx_nic*) ; 
 unsigned int max (unsigned int,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  probe ; 
 scalar_t__ stub1 (struct efx_nic*) ; 

void efx_farch_dimension_resources(struct efx_nic *efx, unsigned sram_lim_qw)
{
	unsigned vi_count, buftbl_min, total_tx_channels;

#ifdef CONFIG_SFC_SRIOV
	struct siena_nic_data *nic_data = efx->nic_data;
#endif

	total_tx_channels = efx->n_tx_channels + efx->n_extra_tx_channels;
	/* Account for the buffer table entries backing the datapath channels
	 * and the descriptor caches for those channels.
	 */
	buftbl_min = ((efx->n_rx_channels * EFX_MAX_DMAQ_SIZE +
		       total_tx_channels * EFX_TXQ_TYPES * EFX_MAX_DMAQ_SIZE +
		       efx->n_channels * EFX_MAX_EVQ_SIZE)
		      * sizeof(efx_qword_t) / EFX_BUF_SIZE);
	vi_count = max(efx->n_channels, total_tx_channels * EFX_TXQ_TYPES);

#ifdef CONFIG_SFC_SRIOV
	if (efx->type->sriov_wanted) {
		if (efx->type->sriov_wanted(efx)) {
			unsigned vi_dc_entries, buftbl_free;
			unsigned entries_per_vf, vf_limit;

			nic_data->vf_buftbl_base = buftbl_min;

			vi_dc_entries = RX_DC_ENTRIES + TX_DC_ENTRIES;
			vi_count = max(vi_count, EFX_VI_BASE);
			buftbl_free = (sram_lim_qw - buftbl_min -
				       vi_count * vi_dc_entries);

			entries_per_vf = ((vi_dc_entries +
					   EFX_VF_BUFTBL_PER_VI) *
					  efx_vf_size(efx));
			vf_limit = min(buftbl_free / entries_per_vf,
				       (1024U - EFX_VI_BASE) >> efx->vi_scale);

			if (efx->vf_count > vf_limit) {
				netif_err(efx, probe, efx->net_dev,
					  "Reducing VF count from from %d to %d\n",
					  efx->vf_count, vf_limit);
				efx->vf_count = vf_limit;
			}
			vi_count += efx->vf_count * efx_vf_size(efx);
		}
	}
#endif

	efx->tx_dc_base = sram_lim_qw - vi_count * TX_DC_ENTRIES;
	efx->rx_dc_base = efx->tx_dc_base - vi_count * RX_DC_ENTRIES;
}