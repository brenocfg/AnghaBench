#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct chash_iter {size_t slot; TYPE_1__* table; } ;
struct TYPE_2__ {int key_size; scalar_t__ value_size; int /*<<< orphan*/ * keys64; int /*<<< orphan*/ * keys32; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  chash_iter_set_invalid (struct chash_iter) ; 
 int /*<<< orphan*/  chash_iter_set_valid (struct chash_iter) ; 
 int /*<<< orphan*/  chash_iter_value (struct chash_iter) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void chash_iter_relocate(struct chash_iter dst, struct chash_iter src)
{
	BUG_ON(src.table == dst.table && src.slot == dst.slot);
	BUG_ON(src.table->key_size != dst.table->key_size);
	BUG_ON(src.table->value_size != dst.table->value_size);

	if (dst.table->key_size == 4)
		dst.table->keys32[dst.slot] = src.table->keys32[src.slot];
	else
		dst.table->keys64[dst.slot] = src.table->keys64[src.slot];

	if (dst.table->value_size)
		memcpy(chash_iter_value(dst), chash_iter_value(src),
		       dst.table->value_size);

	chash_iter_set_valid(dst);
	chash_iter_set_invalid(src);

#ifdef CONFIG_CHASH_STATS
	if (src.table == dst.table) {
		dst.table->relocs++;
		dst.table->reloc_dist +=
			CHASH_SUB(dst.table, src.slot, dst.slot);
	}
#endif
}