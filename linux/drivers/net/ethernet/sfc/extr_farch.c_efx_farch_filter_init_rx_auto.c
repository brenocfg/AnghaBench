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
struct efx_nic {scalar_t__ rx_scatter; } ;
struct efx_farch_filter_spec {int flags; scalar_t__ dmaq_id; int /*<<< orphan*/  priority; } ;

/* Variables and functions */
 int EFX_FILTER_FLAG_RX ; 
 int EFX_FILTER_FLAG_RX_RSS ; 
 int EFX_FILTER_FLAG_RX_SCATTER ; 
 int /*<<< orphan*/  EFX_FILTER_PRI_AUTO ; 
 scalar_t__ efx_rss_enabled (struct efx_nic*) ; 

__attribute__((used)) static void
efx_farch_filter_init_rx_auto(struct efx_nic *efx,
			      struct efx_farch_filter_spec *spec)
{
	/* If there's only one channel then disable RSS for non VF
	 * traffic, thereby allowing VFs to use RSS when the PF can't.
	 */
	spec->priority = EFX_FILTER_PRI_AUTO;
	spec->flags = (EFX_FILTER_FLAG_RX |
		       (efx_rss_enabled(efx) ? EFX_FILTER_FLAG_RX_RSS : 0) |
		       (efx->rx_scatter ? EFX_FILTER_FLAG_RX_SCATTER : 0));
	spec->dmaq_id = 0;
}