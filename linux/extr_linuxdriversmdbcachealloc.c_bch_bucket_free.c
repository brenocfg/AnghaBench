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
struct cache_set {int dummy; } ;
struct bkey {int dummy; } ;

/* Variables and functions */
 unsigned int KEY_PTRS (struct bkey*) ; 
 int /*<<< orphan*/  PTR_BUCKET (struct cache_set*,struct bkey*,unsigned int) ; 
 int /*<<< orphan*/  PTR_CACHE (struct cache_set*,struct bkey*,unsigned int) ; 
 int /*<<< orphan*/  __bch_bucket_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bch_bucket_free(struct cache_set *c, struct bkey *k)
{
	unsigned int i;

	for (i = 0; i < KEY_PTRS(k); i++)
		__bch_bucket_free(PTR_CACHE(c, k, i),
				  PTR_BUCKET(c, k, i));
}