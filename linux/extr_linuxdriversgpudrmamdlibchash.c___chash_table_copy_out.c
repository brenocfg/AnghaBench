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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct chash_iter {int slot; } ;
struct __chash_table {int key_size; int /*<<< orphan*/  value_size; int /*<<< orphan*/  bits; } ;

/* Variables and functions */
 struct chash_iter CHASH_ITER_INIT (struct __chash_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chash_iter_set_invalid (struct chash_iter) ; 
 int /*<<< orphan*/  chash_iter_value (struct chash_iter) ; 
 int chash_table_find (struct chash_iter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hash_32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int __chash_table_copy_out(struct __chash_table *table, u64 key,
			   void *value, bool remove)
{
	u32 hash = (table->key_size == 4) ?
		hash_32(key, table->bits) : hash_64(key, table->bits);
	struct chash_iter iter = CHASH_ITER_INIT(table, hash);
	int r = chash_table_find(&iter, key, remove);

	if (r < 0)
		return r;

	if (value && table->value_size)
		memcpy(value, chash_iter_value(iter), table->value_size);

	if (remove)
		chash_iter_set_invalid(iter);

	return iter.slot;
}