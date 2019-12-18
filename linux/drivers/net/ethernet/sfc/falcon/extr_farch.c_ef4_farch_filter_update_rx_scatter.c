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
struct ef4_nic {scalar_t__ n_rx_channels; int /*<<< orphan*/  filter_lock; scalar_t__ rx_scatter; struct ef4_farch_filter_state* filter_state; } ;
struct ef4_farch_filter_table {unsigned int size; unsigned int step; scalar_t__ offset; TYPE_1__* spec; int /*<<< orphan*/  used_bitmap; } ;
struct ef4_farch_filter_state {struct ef4_farch_filter_table* table; } ;
typedef  enum ef4_farch_filter_table_id { ____Placeholder_ef4_farch_filter_table_id } ef4_farch_filter_table_id ;
typedef  int /*<<< orphan*/  ef4_oword_t ;
struct TYPE_2__ {scalar_t__ dmaq_id; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EF4_FARCH_FILTER_TABLE_RX_DEF ; 
 int EF4_FARCH_FILTER_TABLE_RX_IP ; 
 int /*<<< orphan*/  EF4_FILTER_FLAG_RX_SCATTER ; 
 int /*<<< orphan*/  ef4_farch_filter_build (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ef4_farch_filter_push_rx_config (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_writeo (struct ef4_nic*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (unsigned int,int /*<<< orphan*/ ) ; 

void ef4_farch_filter_update_rx_scatter(struct ef4_nic *efx)
{
	struct ef4_farch_filter_state *state = efx->filter_state;
	enum ef4_farch_filter_table_id table_id;
	struct ef4_farch_filter_table *table;
	ef4_oword_t filter;
	unsigned int filter_idx;

	spin_lock_bh(&efx->filter_lock);

	for (table_id = EF4_FARCH_FILTER_TABLE_RX_IP;
	     table_id <= EF4_FARCH_FILTER_TABLE_RX_DEF;
	     table_id++) {
		table = &state->table[table_id];

		for (filter_idx = 0; filter_idx < table->size; filter_idx++) {
			if (!test_bit(filter_idx, table->used_bitmap) ||
			    table->spec[filter_idx].dmaq_id >=
			    efx->n_rx_channels)
				continue;

			if (efx->rx_scatter)
				table->spec[filter_idx].flags |=
					EF4_FILTER_FLAG_RX_SCATTER;
			else
				table->spec[filter_idx].flags &=
					~EF4_FILTER_FLAG_RX_SCATTER;

			if (table_id == EF4_FARCH_FILTER_TABLE_RX_DEF)
				/* Pushed by ef4_farch_filter_push_rx_config() */
				continue;

			ef4_farch_filter_build(&filter, &table->spec[filter_idx]);
			ef4_writeo(efx, &filter,
				   table->offset + table->step * filter_idx);
		}
	}

	ef4_farch_filter_push_rx_config(efx);

	spin_unlock_bh(&efx->filter_lock);
}