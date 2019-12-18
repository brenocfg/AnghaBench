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
struct ef4_nic {int dummy; } ;
struct ef4_farch_filter_table {scalar_t__ offset; scalar_t__ used; unsigned int step; scalar_t__ id; int /*<<< orphan*/ * search_limit; int /*<<< orphan*/ * spec; int /*<<< orphan*/  used_bitmap; } ;
typedef  int /*<<< orphan*/  ef4_oword_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ EF4_FARCH_FILTER_TABLE_TX_MAC ; 
 int /*<<< orphan*/  EF4_WARN_ON_PARANOID (int) ; 
 int /*<<< orphan*/  __clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ef4_farch_filter_push_rx_config (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_farch_filter_push_tx_limits (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_writeo (struct ef4_nic*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_bit (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
ef4_farch_filter_table_clear_entry(struct ef4_nic *efx,
				   struct ef4_farch_filter_table *table,
				   unsigned int filter_idx)
{
	static ef4_oword_t filter;

	EF4_WARN_ON_PARANOID(!test_bit(filter_idx, table->used_bitmap));
	BUG_ON(table->offset == 0); /* can't clear MAC default filters */

	__clear_bit(filter_idx, table->used_bitmap);
	--table->used;
	memset(&table->spec[filter_idx], 0, sizeof(table->spec[0]));

	ef4_writeo(efx, &filter, table->offset + table->step * filter_idx);

	/* If this filter required a greater search depth than
	 * any other, the search limit for its type can now be
	 * decreased.  However, it is hard to determine that
	 * unless the table has become completely empty - in
	 * which case, all its search limits can be set to 0.
	 */
	if (unlikely(table->used == 0)) {
		memset(table->search_limit, 0, sizeof(table->search_limit));
		if (table->id == EF4_FARCH_FILTER_TABLE_TX_MAC)
			ef4_farch_filter_push_tx_limits(efx);
		else
			ef4_farch_filter_push_rx_config(efx);
	}
}