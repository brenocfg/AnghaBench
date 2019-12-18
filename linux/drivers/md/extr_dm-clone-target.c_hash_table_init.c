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
struct hash_table_bucket {int /*<<< orphan*/  lock; int /*<<< orphan*/  head; } ;
struct clone {struct hash_table_bucket* ht; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HASH_TABLE_BITS ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 struct hash_table_bucket* kvmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hash_table_init(struct clone *clone)
{
	unsigned int i, sz;
	struct hash_table_bucket *bucket;

	sz = 1 << HASH_TABLE_BITS;

	clone->ht = kvmalloc(sz * sizeof(struct hash_table_bucket), GFP_KERNEL);
	if (!clone->ht)
		return -ENOMEM;

	for (i = 0; i < sz; i++) {
		bucket = clone->ht + i;

		INIT_HLIST_HEAD(&bucket->head);
		spin_lock_init(&bucket->lock);
	}

	return 0;
}