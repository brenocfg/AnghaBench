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
struct cache_set {int dummy; } ;
struct bkey {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pin; } ;

/* Variables and functions */
 unsigned int KEY_PTRS (struct bkey*) ; 
 TYPE_1__* PTR_BUCKET (struct cache_set*,struct bkey*,unsigned int) ; 
 int /*<<< orphan*/  atomic_dec_bug (int /*<<< orphan*/ *) ; 
 scalar_t__ ptr_available (struct cache_set*,struct bkey*,unsigned int) ; 

void bkey_put(struct cache_set *c, struct bkey *k)
{
	unsigned int i;

	for (i = 0; i < KEY_PTRS(k); i++)
		if (ptr_available(c, k, i))
			atomic_dec_bug(&PTR_BUCKET(c, k, i)->pin);
}