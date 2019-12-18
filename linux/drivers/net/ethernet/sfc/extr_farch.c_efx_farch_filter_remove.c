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
struct efx_farch_filter_table {int /*<<< orphan*/  used_bitmap; struct efx_farch_filter_spec* spec; } ;
struct efx_farch_filter_spec {int priority; int flags; } ;
typedef  enum efx_filter_priority { ____Placeholder_efx_filter_priority } efx_filter_priority ;

/* Variables and functions */
 int EFX_FILTER_FLAG_RX_OVER_AUTO ; 
 int ENOENT ; 
 int /*<<< orphan*/  efx_farch_filter_init_rx_auto (struct efx_nic*,struct efx_farch_filter_spec*) ; 
 int /*<<< orphan*/  efx_farch_filter_push_rx_config (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_farch_filter_table_clear_entry (struct efx_nic*,struct efx_farch_filter_table*,unsigned int) ; 
 int /*<<< orphan*/  test_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efx_farch_filter_remove(struct efx_nic *efx,
				   struct efx_farch_filter_table *table,
				   unsigned int filter_idx,
				   enum efx_filter_priority priority)
{
	struct efx_farch_filter_spec *spec = &table->spec[filter_idx];

	if (!test_bit(filter_idx, table->used_bitmap) ||
	    spec->priority != priority)
		return -ENOENT;

	if (spec->flags & EFX_FILTER_FLAG_RX_OVER_AUTO) {
		efx_farch_filter_init_rx_auto(efx, spec);
		efx_farch_filter_push_rx_config(efx);
	} else {
		efx_farch_filter_table_clear_entry(efx, table, filter_idx);
	}

	return 0;
}