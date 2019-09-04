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
struct keylist {int /*<<< orphan*/  inline_keys; int /*<<< orphan*/  keys_p; int /*<<< orphan*/  top_p; } ;

/* Variables and functions */

__attribute__((used)) static inline void bch_keylist_init(struct keylist *l)
{
	l->top_p = l->keys_p = l->inline_keys;
}