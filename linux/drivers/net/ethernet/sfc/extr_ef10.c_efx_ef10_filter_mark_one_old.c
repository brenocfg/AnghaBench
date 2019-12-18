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
typedef  scalar_t__ uint16_t ;
struct efx_nic {int /*<<< orphan*/  net_dev; struct efx_ef10_filter_table* filter_state; } ;
struct efx_ef10_filter_table {TYPE_1__* entry; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_EF10_FILTER_FLAG_AUTO_OLD ; 
 scalar_t__ EFX_EF10_FILTER_ID_INVALID ; 
 int /*<<< orphan*/  drv ; 
 unsigned int efx_ef10_filter_get_unsafe_id (scalar_t__) ; 
 int /*<<< orphan*/  efx_rwsem_assert_write_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,unsigned int) ; 

__attribute__((used)) static void efx_ef10_filter_mark_one_old(struct efx_nic *efx, uint16_t *id)
{
	struct efx_ef10_filter_table *table = efx->filter_state;
	unsigned int filter_idx;

	efx_rwsem_assert_write_locked(&table->lock);

	if (*id != EFX_EF10_FILTER_ID_INVALID) {
		filter_idx = efx_ef10_filter_get_unsafe_id(*id);
		if (!table->entry[filter_idx].spec)
			netif_dbg(efx, drv, efx->net_dev,
				  "marked null spec old %04x:%04x\n", *id,
				  filter_idx);
		table->entry[filter_idx].spec |= EFX_EF10_FILTER_FLAG_AUTO_OLD;
		*id = EFX_EF10_FILTER_ID_INVALID;
	}
}