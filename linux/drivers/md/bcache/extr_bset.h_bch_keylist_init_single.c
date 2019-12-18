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
struct keylist {int /*<<< orphan*/  top; struct bkey* keys; } ;
struct bkey {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bkey_next (struct bkey*) ; 

__attribute__((used)) static inline void bch_keylist_init_single(struct keylist *l, struct bkey *k)
{
	l->keys = k;
	l->top = bkey_next(k);
}