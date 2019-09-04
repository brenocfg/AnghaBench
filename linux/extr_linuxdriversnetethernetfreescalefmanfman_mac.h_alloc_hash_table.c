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
typedef  size_t u32 ;
typedef  size_t u16 ;
struct list_head {int dummy; } ;
struct eth_hash_t {size_t size; int /*<<< orphan*/ * lsts; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct eth_hash_t*) ; 
 void* kmalloc_array (size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct eth_hash_t *alloc_hash_table(u16 size)
{
	u32 i;
	struct eth_hash_t *hash;

	/* Allocate address hash table */
	hash = kmalloc_array(size, sizeof(struct eth_hash_t *), GFP_KERNEL);
	if (!hash)
		return NULL;

	hash->size = size;

	hash->lsts = kmalloc_array(hash->size, sizeof(struct list_head),
				   GFP_KERNEL);
	if (!hash->lsts) {
		kfree(hash);
		return NULL;
	}

	for (i = 0; i < hash->size; i++)
		INIT_LIST_HEAD(&hash->lsts[i]);

	return hash;
}