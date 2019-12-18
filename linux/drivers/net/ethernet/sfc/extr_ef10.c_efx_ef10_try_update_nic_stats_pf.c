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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__* addr; } ;
struct efx_nic {int num_mac_stats; TYPE_1__ stats_buffer; struct efx_ef10_nic_data* nic_data; } ;
struct efx_ef10_nic_data {scalar_t__* stats; } ;
typedef  scalar_t__ __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_BITMAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int /*<<< orphan*/  EF10_STAT_COUNT ; 
 size_t EF10_STAT_port_rx_bad_bytes ; 
 size_t EF10_STAT_port_rx_bytes ; 
 size_t EF10_STAT_port_rx_bytes_minus_good_bytes ; 
 size_t EF10_STAT_port_rx_good_bytes ; 
 size_t EF10_STAT_port_rx_nodesc_drops ; 
 scalar_t__ EFX_MC_STATS_GENERATION_INVALID ; 
 size_t MC_CMD_MAC_GENERATION_START ; 
 int /*<<< orphan*/  efx_ef10_get_stat_mask (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_ef10_stat_desc ; 
 int /*<<< orphan*/  efx_nic_fix_nodesc_drop_stat (struct efx_nic*,scalar_t__*) ; 
 int /*<<< orphan*/  efx_nic_update_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  efx_update_diff_stat (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  efx_update_sw_stats (struct efx_nic*,scalar_t__*) ; 
 int /*<<< orphan*/  mask ; 
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static int efx_ef10_try_update_nic_stats_pf(struct efx_nic *efx)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;
	DECLARE_BITMAP(mask, EF10_STAT_COUNT);
	__le64 generation_start, generation_end;
	u64 *stats = nic_data->stats;
	__le64 *dma_stats;

	efx_ef10_get_stat_mask(efx, mask);

	dma_stats = efx->stats_buffer.addr;

	generation_end = dma_stats[efx->num_mac_stats - 1];
	if (generation_end == EFX_MC_STATS_GENERATION_INVALID)
		return 0;
	rmb();
	efx_nic_update_stats(efx_ef10_stat_desc, EF10_STAT_COUNT, mask,
			     stats, efx->stats_buffer.addr, false);
	rmb();
	generation_start = dma_stats[MC_CMD_MAC_GENERATION_START];
	if (generation_end != generation_start)
		return -EAGAIN;

	/* Update derived statistics */
	efx_nic_fix_nodesc_drop_stat(efx,
				     &stats[EF10_STAT_port_rx_nodesc_drops]);
	stats[EF10_STAT_port_rx_good_bytes] =
		stats[EF10_STAT_port_rx_bytes] -
		stats[EF10_STAT_port_rx_bytes_minus_good_bytes];
	efx_update_diff_stat(&stats[EF10_STAT_port_rx_bad_bytes],
			     stats[EF10_STAT_port_rx_bytes_minus_good_bytes]);
	efx_update_sw_stats(efx, stats);
	return 0;
}