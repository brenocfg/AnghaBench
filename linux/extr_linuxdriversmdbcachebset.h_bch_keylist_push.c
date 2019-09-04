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
struct keylist {int /*<<< orphan*/  top; } ;

/* Variables and functions */
 int /*<<< orphan*/  bkey_next (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void bch_keylist_push(struct keylist *l)
{
	l->top = bkey_next(l->top);
}