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
struct keylist {int dummy; } ;
struct jset {int dummy; } ;
struct cache_set {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int __bch_keylist_realloc (struct keylist*,unsigned int) ; 
 size_t bch_keylist_nkeys (struct keylist*) ; 
 int block_bytes (struct cache_set*) ; 

__attribute__((used)) static int bch_keylist_realloc(struct keylist *l, unsigned int u64s,
			       struct cache_set *c)
{
	size_t oldsize = bch_keylist_nkeys(l);
	size_t newsize = oldsize + u64s;

	/*
	 * The journalling code doesn't handle the case where the keys to insert
	 * is bigger than an empty write: If we just return -ENOMEM here,
	 * bch_data_insert_keys() will insert the keys created so far
	 * and finish the rest when the keylist is empty.
	 */
	if (newsize * sizeof(uint64_t) > block_bytes(c) - sizeof(struct jset))
		return -ENOMEM;

	return __bch_keylist_realloc(l, u64s);
}