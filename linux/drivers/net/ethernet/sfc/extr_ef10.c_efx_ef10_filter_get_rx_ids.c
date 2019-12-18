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
typedef  int /*<<< orphan*/  s32 ;
typedef  enum efx_filter_priority { ____Placeholder_efx_filter_priority } efx_filter_priority ;

/* Variables and functions */
 int /*<<< orphan*/  EMSGSIZE ; 
 unsigned int HUNT_FILTER_TBL_ROWS ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct efx_filter_spec* efx_ef10_filter_entry_spec (struct efx_ef10_filter_table*,unsigned int) ; 
 int /*<<< orphan*/  efx_ef10_filter_pri (struct efx_ef10_filter_table*,struct efx_filter_spec*) ; 
 int /*<<< orphan*/  efx_ef10_make_filter_id (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32 efx_ef10_filter_get_rx_ids(struct efx_nic *efx,
				      enum efx_filter_priority priority,
				      u32 *buf, u32 size)
{
	struct efx_ef10_filter_table *table;
	struct efx_filter_spec *spec;
	unsigned int filter_idx;
	s32 count = 0;

	down_read(&efx->filter_sem);
	table = efx->filter_state;
	down_read(&table->lock);

	for (filter_idx = 0; filter_idx < HUNT_FILTER_TBL_ROWS; filter_idx++) {
		spec = efx_ef10_filter_entry_spec(table, filter_idx);
		if (spec && spec->priority == priority) {
			if (count == size) {
				count = -EMSGSIZE;
				break;
			}
			buf[count++] =
				efx_ef10_make_filter_id(
					efx_ef10_filter_pri(table, spec),
					filter_idx);
		}
	}
	up_read(&table->lock);
	up_read(&efx->filter_sem);
	return count;
}