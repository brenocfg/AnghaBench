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
struct keylist {scalar_t__ keys_p; scalar_t__ inline_keys; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (scalar_t__) ; 

__attribute__((used)) static inline void bch_keylist_free(struct keylist *l)
{
	if (l->keys_p != l->inline_keys)
		kfree(l->keys_p);
}