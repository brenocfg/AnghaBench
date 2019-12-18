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
struct efx_nic {int /*<<< orphan*/  filter_sem; struct efx_ef10_filter_table* filter_state; } ;
struct efx_filter_spec {int priority; } ;
struct efx_ef10_filter_table {int /*<<< orphan*/  lock; } ;
typedef  enum efx_filter_priority { ____Placeholder_efx_filter_priority } efx_filter_priority ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct efx_filter_spec* efx_ef10_filter_entry_spec (struct efx_ef10_filter_table*,unsigned int) ; 
 unsigned int efx_ef10_filter_get_unsafe_id (int /*<<< orphan*/ ) ; 
 scalar_t__ efx_ef10_filter_get_unsafe_pri (int /*<<< orphan*/ ) ; 
 scalar_t__ efx_ef10_filter_pri (struct efx_ef10_filter_table*,struct efx_filter_spec const*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int efx_ef10_filter_get_safe(struct efx_nic *efx,
				    enum efx_filter_priority priority,
				    u32 filter_id, struct efx_filter_spec *spec)
{
	unsigned int filter_idx = efx_ef10_filter_get_unsafe_id(filter_id);
	const struct efx_filter_spec *saved_spec;
	struct efx_ef10_filter_table *table;
	int rc;

	down_read(&efx->filter_sem);
	table = efx->filter_state;
	down_read(&table->lock);
	saved_spec = efx_ef10_filter_entry_spec(table, filter_idx);
	if (saved_spec && saved_spec->priority == priority &&
	    efx_ef10_filter_pri(table, saved_spec) ==
	    efx_ef10_filter_get_unsafe_pri(filter_id)) {
		*spec = *saved_spec;
		rc = 0;
	} else {
		rc = -ENOENT;
	}
	up_read(&table->lock);
	up_read(&efx->filter_sem);
	return rc;
}