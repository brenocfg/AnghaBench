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
struct list_head {int /*<<< orphan*/  next; } ;
struct eth_hash_entry {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 struct eth_hash_entry* ETH_HASH_ENTRY_OBJ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 

__attribute__((used)) static inline struct eth_hash_entry
*dequeue_addr_from_hash_entry(struct list_head *addr_lst)
{
	struct eth_hash_entry *hash_entry = NULL;

	if (!list_empty(addr_lst)) {
		hash_entry = ETH_HASH_ENTRY_OBJ(addr_lst->next);
		list_del_init(&hash_entry->node);
	}
	return hash_entry;
}