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
struct tlb_client_info {int load_history; int tx_bytes; void* prev; void* next; int /*<<< orphan*/ * tx_slave; } ;

/* Variables and functions */
 int BOND_TLB_REBALANCE_INTERVAL ; 
 void* TLB_NULL_INDEX ; 

__attribute__((used)) static inline void tlb_init_table_entry(struct tlb_client_info *entry, int save_load)
{
	if (save_load) {
		entry->load_history = 1 + entry->tx_bytes /
				      BOND_TLB_REBALANCE_INTERVAL;
		entry->tx_bytes = 0;
	}

	entry->tx_slave = NULL;
	entry->next = TLB_NULL_INDEX;
	entry->prev = TLB_NULL_INDEX;
}