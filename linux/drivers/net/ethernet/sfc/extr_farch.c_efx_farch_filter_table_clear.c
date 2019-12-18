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
struct efx_nic {struct efx_farch_filter_state* filter_state; } ;
struct efx_farch_filter_table {unsigned int size; TYPE_1__* spec; } ;
struct efx_farch_filter_state {int /*<<< orphan*/  lock; struct efx_farch_filter_table* table; } ;
typedef  enum efx_filter_priority { ____Placeholder_efx_filter_priority } efx_filter_priority ;
typedef  enum efx_farch_filter_table_id { ____Placeholder_efx_farch_filter_table_id } efx_farch_filter_table_id ;
struct TYPE_2__ {scalar_t__ priority; } ;

/* Variables and functions */
 scalar_t__ EFX_FILTER_PRI_AUTO ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_farch_filter_remove (struct efx_nic*,struct efx_farch_filter_table*,unsigned int,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
efx_farch_filter_table_clear(struct efx_nic *efx,
			     enum efx_farch_filter_table_id table_id,
			     enum efx_filter_priority priority)
{
	struct efx_farch_filter_state *state = efx->filter_state;
	struct efx_farch_filter_table *table = &state->table[table_id];
	unsigned int filter_idx;

	down_write(&state->lock);
	for (filter_idx = 0; filter_idx < table->size; ++filter_idx) {
		if (table->spec[filter_idx].priority != EFX_FILTER_PRI_AUTO)
			efx_farch_filter_remove(efx, table,
						filter_idx, priority);
	}
	up_write(&state->lock);
}