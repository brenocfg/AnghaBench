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
struct smq_hash_table {int /*<<< orphan*/  hash_bits; } ;
struct entry {int dummy; } ;
typedef  int /*<<< orphan*/  dm_oblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  __h_insert (struct smq_hash_table*,unsigned int,struct entry*) ; 
 struct entry* __h_lookup (struct smq_hash_table*,unsigned int,int /*<<< orphan*/ ,struct entry**) ; 
 int /*<<< orphan*/  __h_unlink (struct smq_hash_table*,unsigned int,struct entry*,struct entry*) ; 
 int /*<<< orphan*/  from_oblock (int /*<<< orphan*/ ) ; 
 unsigned int hash_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct entry *h_lookup(struct smq_hash_table *ht, dm_oblock_t oblock)
{
	struct entry *e, *prev;
	unsigned h = hash_64(from_oblock(oblock), ht->hash_bits);

	e = __h_lookup(ht, h, oblock, &prev);
	if (e && prev) {
		/*
		 * Move to the front because this entry is likely
		 * to be hit again.
		 */
		__h_unlink(ht, h, e, prev);
		__h_insert(ht, h, e);
	}

	return e;
}