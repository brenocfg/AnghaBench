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
struct eth_hash_t {int size; struct eth_hash_t* lsts; } ;
struct eth_hash_entry {int size; struct eth_hash_entry* lsts; } ;

/* Variables and functions */
 struct eth_hash_t* dequeue_addr_from_hash_entry (struct eth_hash_t*) ; 
 int /*<<< orphan*/  kfree (struct eth_hash_t*) ; 

__attribute__((used)) static inline void free_hash_table(struct eth_hash_t *hash)
{
	struct eth_hash_entry *hash_entry;
	int i = 0;

	if (hash) {
		if (hash->lsts) {
			for (i = 0; i < hash->size; i++) {
				hash_entry =
				dequeue_addr_from_hash_entry(&hash->lsts[i]);
				while (hash_entry) {
					kfree(hash_entry);
					hash_entry =
					dequeue_addr_from_hash_entry(&hash->
								     lsts[i]);
				}
			}

			kfree(hash->lsts);
		}

		kfree(hash);
	}
}