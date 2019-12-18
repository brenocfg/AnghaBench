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
struct entry {int /*<<< orphan*/  oblock; } ;

/* Variables and functions */
 struct entry* __h_lookup (struct smq_hash_table*,unsigned int,int /*<<< orphan*/ ,struct entry**) ; 
 int /*<<< orphan*/  __h_unlink (struct smq_hash_table*,unsigned int,struct entry*,struct entry*) ; 
 int /*<<< orphan*/  from_oblock (int /*<<< orphan*/ ) ; 
 unsigned int hash_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void h_remove(struct smq_hash_table *ht, struct entry *e)
{
	unsigned h = hash_64(from_oblock(e->oblock), ht->hash_bits);
	struct entry *prev;

	/*
	 * The down side of using a singly linked list is we have to
	 * iterate the bucket to remove an item.
	 */
	e = __h_lookup(ht, h, e->oblock, &prev);
	if (e)
		__h_unlink(ht, h, e, prev);
}