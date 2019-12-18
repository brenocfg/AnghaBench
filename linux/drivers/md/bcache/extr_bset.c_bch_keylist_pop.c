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
struct keylist {struct bkey* top; struct bkey* keys; } ;
struct bkey {int dummy; } ;

/* Variables and functions */
 struct bkey* bkey_next (struct bkey*) ; 

struct bkey *bch_keylist_pop(struct keylist *l)
{
	struct bkey *k = l->keys;

	if (k == l->top)
		return NULL;

	while (bkey_next(k) != l->top)
		k = bkey_next(k);

	return l->top = k;
}