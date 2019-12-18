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
typedef  int /*<<< orphan*/  u32 ;
struct efx_nic {struct efx_farch_filter_state* filter_state; } ;
struct efx_filter_spec {int dummy; } ;
struct efx_farch_filter_table {unsigned int size; int /*<<< orphan*/  used_bitmap; struct efx_farch_filter_spec* spec; } ;
struct efx_farch_filter_state {int /*<<< orphan*/  lock; struct efx_farch_filter_table* table; } ;
struct efx_farch_filter_spec {int priority; } ;
typedef  enum efx_filter_priority { ____Placeholder_efx_filter_priority } efx_filter_priority ;
typedef  enum efx_farch_filter_table_id { ____Placeholder_efx_farch_filter_table_id } efx_farch_filter_table_id ;

/* Variables and functions */
 unsigned int EFX_FARCH_FILTER_TABLE_COUNT ; 
 int ENOENT ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 unsigned int efx_farch_filter_id_index (int /*<<< orphan*/ ) ; 
 int efx_farch_filter_id_table_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_farch_filter_to_gen_spec (struct efx_filter_spec*,struct efx_farch_filter_spec*) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int efx_farch_filter_get_safe(struct efx_nic *efx,
			      enum efx_filter_priority priority,
			      u32 filter_id, struct efx_filter_spec *spec_buf)
{
	struct efx_farch_filter_state *state = efx->filter_state;
	enum efx_farch_filter_table_id table_id;
	struct efx_farch_filter_table *table;
	struct efx_farch_filter_spec *spec;
	unsigned int filter_idx;
	int rc = -ENOENT;

	down_read(&state->lock);

	table_id = efx_farch_filter_id_table_id(filter_id);
	if ((unsigned int)table_id >= EFX_FARCH_FILTER_TABLE_COUNT)
		goto out_unlock;
	table = &state->table[table_id];

	filter_idx = efx_farch_filter_id_index(filter_id);
	if (filter_idx >= table->size)
		goto out_unlock;
	spec = &table->spec[filter_idx];

	if (test_bit(filter_idx, table->used_bitmap) &&
	    spec->priority == priority) {
		efx_farch_filter_to_gen_spec(spec_buf, spec);
		rc = 0;
	}

out_unlock:
	up_read(&state->lock);
	return rc;
}