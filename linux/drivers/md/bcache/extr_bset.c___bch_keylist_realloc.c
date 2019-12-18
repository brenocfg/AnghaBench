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
typedef  int /*<<< orphan*/  uint64_t ;
struct keylist {int /*<<< orphan*/ * top_p; int /*<<< orphan*/ * keys_p; int /*<<< orphan*/ * inline_keys; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 size_t KEYLIST_INLINE ; 
 size_t bch_keylist_nkeys (struct keylist*) ; 
 int /*<<< orphan*/ * krealloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 size_t roundup_pow_of_two (size_t) ; 

int __bch_keylist_realloc(struct keylist *l, unsigned int u64s)
{
	size_t oldsize = bch_keylist_nkeys(l);
	size_t newsize = oldsize + u64s;
	uint64_t *old_keys = l->keys_p == l->inline_keys ? NULL : l->keys_p;
	uint64_t *new_keys;

	newsize = roundup_pow_of_two(newsize);

	if (newsize <= KEYLIST_INLINE ||
	    roundup_pow_of_two(oldsize) == newsize)
		return 0;

	new_keys = krealloc(old_keys, sizeof(uint64_t) * newsize, GFP_NOIO);

	if (!new_keys)
		return -ENOMEM;

	if (!old_keys)
		memcpy(new_keys, l->inline_keys, sizeof(uint64_t) * oldsize);

	l->keys_p = new_keys;
	l->top_p = new_keys + oldsize;

	return 0;
}