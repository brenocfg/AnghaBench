#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct tlb_client_info {size_t next; } ;
struct slave {int dummy; } ;
struct bonding {int dummy; } ;
struct TYPE_4__ {struct tlb_client_info* tx_hashtbl; } ;
struct TYPE_3__ {size_t head; } ;

/* Variables and functions */
 TYPE_2__ BOND_ALB_INFO (struct bonding*) ; 
 TYPE_1__ SLAVE_TLB_INFO (struct slave*) ; 
 size_t TLB_NULL_INDEX ; 
 int /*<<< orphan*/  tlb_init_slave (struct slave*) ; 
 int /*<<< orphan*/  tlb_init_table_entry (struct tlb_client_info*,int) ; 

__attribute__((used)) static void __tlb_clear_slave(struct bonding *bond, struct slave *slave,
			 int save_load)
{
	struct tlb_client_info *tx_hash_table;
	u32 index;

	/* clear slave from tx_hashtbl */
	tx_hash_table = BOND_ALB_INFO(bond).tx_hashtbl;

	/* skip this if we've already freed the tx hash table */
	if (tx_hash_table) {
		index = SLAVE_TLB_INFO(slave).head;
		while (index != TLB_NULL_INDEX) {
			u32 next_index = tx_hash_table[index].next;
			tlb_init_table_entry(&tx_hash_table[index], save_load);
			index = next_index;
		}
	}

	tlb_init_slave(slave);
}