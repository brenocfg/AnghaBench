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
struct smq_hash_table {int /*<<< orphan*/ * buckets; int /*<<< orphan*/  hash_bits; struct entry_space* es; } ;
struct entry_space {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INDEXER_NULL ; 
 int /*<<< orphan*/  __ffs (unsigned int) ; 
 int /*<<< orphan*/  array_size (unsigned int,int) ; 
 int /*<<< orphan*/  max (unsigned int,unsigned int) ; 
 unsigned int roundup_pow_of_two (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int h_init(struct smq_hash_table *ht, struct entry_space *es, unsigned nr_entries)
{
	unsigned i, nr_buckets;

	ht->es = es;
	nr_buckets = roundup_pow_of_two(max(nr_entries / 4u, 16u));
	ht->hash_bits = __ffs(nr_buckets);

	ht->buckets = vmalloc(array_size(nr_buckets, sizeof(*ht->buckets)));
	if (!ht->buckets)
		return -ENOMEM;

	for (i = 0; i < nr_buckets; i++)
		ht->buckets[i] = INDEXER_NULL;

	return 0;
}