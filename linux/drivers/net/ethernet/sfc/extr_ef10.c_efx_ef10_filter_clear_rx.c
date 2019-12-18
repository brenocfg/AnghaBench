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
struct efx_nic {int /*<<< orphan*/  filter_sem; struct efx_ef10_filter_table* filter_state; } ;
struct efx_ef10_filter_table {int /*<<< orphan*/  lock; } ;
typedef  enum efx_filter_priority { ____Placeholder_efx_filter_priority } efx_filter_priority ;

/* Variables and functions */
 unsigned int EFX_FILTER_PRI_AUTO ; 
 int ENOENT ; 
 unsigned int HUNT_FILTER_TBL_ROWS ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int efx_ef10_filter_remove_internal (struct efx_nic*,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int efx_ef10_filter_clear_rx(struct efx_nic *efx,
				    enum efx_filter_priority priority)
{
	struct efx_ef10_filter_table *table;
	unsigned int priority_mask;
	unsigned int i;
	int rc;

	priority_mask = (((1U << (priority + 1)) - 1) &
			 ~(1U << EFX_FILTER_PRI_AUTO));

	down_read(&efx->filter_sem);
	table = efx->filter_state;
	down_write(&table->lock);
	for (i = 0; i < HUNT_FILTER_TBL_ROWS; i++) {
		rc = efx_ef10_filter_remove_internal(efx, priority_mask,
						     i, true);
		if (rc && rc != -ENOENT)
			break;
		rc = 0;
	}

	up_write(&table->lock);
	up_read(&efx->filter_sem);
	return rc;
}