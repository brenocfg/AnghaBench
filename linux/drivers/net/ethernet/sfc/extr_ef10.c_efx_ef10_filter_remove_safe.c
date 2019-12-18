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
struct efx_ef10_filter_table {int /*<<< orphan*/  lock; } ;
typedef  enum efx_filter_priority { ____Placeholder_efx_filter_priority } efx_filter_priority ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int efx_ef10_filter_remove_internal (struct efx_nic*,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int efx_ef10_filter_remove_safe(struct efx_nic *efx,
				       enum efx_filter_priority priority,
				       u32 filter_id)
{
	struct efx_ef10_filter_table *table;
	int rc;

	down_read(&efx->filter_sem);
	table = efx->filter_state;
	down_write(&table->lock);
	rc = efx_ef10_filter_remove_internal(efx, 1U << priority, filter_id,
					     false);
	up_write(&table->lock);
	up_read(&efx->filter_sem);
	return rc;
}