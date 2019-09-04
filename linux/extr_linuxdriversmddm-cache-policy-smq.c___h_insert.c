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
struct smq_hash_table {int /*<<< orphan*/  es; int /*<<< orphan*/ * buckets; } ;
struct entry {int /*<<< orphan*/  hash_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  to_index (int /*<<< orphan*/ ,struct entry*) ; 

__attribute__((used)) static void __h_insert(struct smq_hash_table *ht, unsigned bucket, struct entry *e)
{
	e->hash_next = ht->buckets[bucket];
	ht->buckets[bucket] = to_index(ht->es, e);
}