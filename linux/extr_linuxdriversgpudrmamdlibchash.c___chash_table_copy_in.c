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
typedef  void* u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct chash_iter {size_t slot; } ;
struct __chash_table {int key_size; int /*<<< orphan*/  value_size; void** keys64; void** keys32; int /*<<< orphan*/  bits; } ;

/* Variables and functions */
 struct chash_iter CHASH_ITER_INIT (struct __chash_table*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  chash_iter_set_valid (struct chash_iter) ; 
 int /*<<< orphan*/  chash_iter_value (struct chash_iter) ; 
 int chash_table_find (struct chash_iter*,void*,int) ; 
 int /*<<< orphan*/  hash_32 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_64 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int __chash_table_copy_in(struct __chash_table *table, u64 key,
			  const void *value)
{
	u32 hash = (table->key_size == 4) ?
		hash_32(key, table->bits) : hash_64(key, table->bits);
	struct chash_iter iter = CHASH_ITER_INIT(table, hash);
	int r = chash_table_find(&iter, key, false);

	/* Found an existing entry */
	if (!r) {
		if (value && table->value_size)
			memcpy(chash_iter_value(iter), value,
			       table->value_size);
		return 1;
	}

	/* Is there a place to add a new entry? */
	if (iter.slot < 0) {
		pr_err("Hash table overflow\n");
		return -ENOMEM;
	}

	chash_iter_set_valid(iter);

	if (table->key_size == 4)
		table->keys32[iter.slot] = key;
	else
		table->keys64[iter.slot] = key;
	if (value && table->value_size)
		memcpy(chash_iter_value(iter), value, table->value_size);

	return 0;
}