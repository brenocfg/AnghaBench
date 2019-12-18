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
struct keylist {int /*<<< orphan*/  keys; int /*<<< orphan*/  top_p; } ;

/* Variables and functions */
 int /*<<< orphan*/  bch_keylist_bytes (struct keylist*) ; 
 int /*<<< orphan*/  bkey_next (int /*<<< orphan*/ ) ; 
 scalar_t__ bkey_u64s (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bch_keylist_pop_front(struct keylist *l)
{
	l->top_p -= bkey_u64s(l->keys);

	memmove(l->keys,
		bkey_next(l->keys),
		bch_keylist_bytes(l));
}