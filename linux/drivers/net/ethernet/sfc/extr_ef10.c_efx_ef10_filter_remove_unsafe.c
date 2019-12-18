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
typedef  scalar_t__ u32 ;
struct efx_nic {struct efx_ef10_filter_table* filter_state; } ;
struct efx_ef10_filter_table {int /*<<< orphan*/  lock; } ;
typedef  enum efx_filter_priority { ____Placeholder_efx_filter_priority } efx_filter_priority ;

/* Variables and functions */
 scalar_t__ EFX_EF10_FILTER_ID_INVALID ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_ef10_filter_remove_internal (struct efx_nic*,unsigned int,scalar_t__,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void efx_ef10_filter_remove_unsafe(struct efx_nic *efx,
					  enum efx_filter_priority priority,
					  u32 filter_id)
{
	struct efx_ef10_filter_table *table = efx->filter_state;

	if (filter_id == EFX_EF10_FILTER_ID_INVALID)
		return;

	down_write(&table->lock);
	efx_ef10_filter_remove_internal(efx, 1U << priority, filter_id,
					true);
	up_write(&table->lock);
}